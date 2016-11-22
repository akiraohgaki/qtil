/**
 * A library for Qt app
 *
 * LICENSE: The GNU Lesser General Public License, version 3.0
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0  The GNU Lesser General Public License, version 3.0
 * @link        https://github.com/akiraohgaki/qtlibs
 */

#include "networkresource.h"

#include <QEventLoop>

#include "file.h"

namespace qtlibs {

NetworkResource::NetworkResource(const QString &name, const QUrl &url, bool async, QObject *parent)
    : QObject(parent), name_(name), url_(url), async_(async)
{
    setManager(new QNetworkAccessManager(this));
}

NetworkResource::~NetworkResource()
{
    manager()->deleteLater();
}

NetworkResource::NetworkResource(const NetworkResource &other, QObject *parent)
    : QObject(parent)
{
    setName(other.name());
    setUrl(other.url());
    setAsync(other.async());
    setRequest(other.request());
    setManager(new QNetworkAccessManager(this));
}

NetworkResource &NetworkResource::operator =(const NetworkResource &other)
{
    setName(other.name());
    setUrl(other.url());
    setAsync(other.async());
    setRequest(other.request());
    return *this;
}

QString NetworkResource::name() const
{
    return name_;
}

void NetworkResource::setName(const QString &name)
{
    name_ = name;
}

QUrl NetworkResource::url() const
{
    return url_;
}

void NetworkResource::setUrl(const QUrl &url)
{
    url_ = url;
}

bool NetworkResource::async() const
{
    return async_;
}

void NetworkResource::setAsync(bool async)
{
    async_ = async;
}

QNetworkRequest NetworkResource::request() const
{
    return request_;
}

void NetworkResource::setRequest(const QNetworkRequest &request)
{
    request_ = request;
}

QNetworkAccessManager *NetworkResource::manager() const
{
    return manager_;
}

QNetworkReply *NetworkResource::reply() const
{
    return reply_;
}

QString NetworkResource::method() const
{
    return method_;
}

QUrlQuery NetworkResource::formData() const
{
    return formData_;
}

NetworkResource *NetworkResource::head()
{
    QNetworkRequest networkRequest = request();
    networkRequest.setUrl(url());
    return send(async(), "HEAD", networkRequest);
}

NetworkResource *NetworkResource::get()
{
    QNetworkRequest networkRequest = request();
    networkRequest.setUrl(url());
    return send(async(), "GET", networkRequest);
}

NetworkResource *NetworkResource::post(const QUrlQuery &formData)
{
    QNetworkRequest networkRequest = request();
    networkRequest.setUrl(url());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    return send(async(), "POST", networkRequest, formData);
}

NetworkResource *NetworkResource::put(const QUrlQuery &formData)
{
    QNetworkRequest networkRequest = request();
    networkRequest.setUrl(url());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    return send(async(), "PUT", networkRequest, formData);
}

NetworkResource *NetworkResource::deleteResource()
{
    QNetworkRequest networkRequest = request();
    networkRequest.setUrl(url());
    return send(async(), "DELETE", networkRequest);
}

bool NetworkResource::isFinishedWithNoError()
{
    if (reply()->isFinished() && reply()->error() == QNetworkReply::NoError) {
        return true;
    }
    return false;
}

QByteArray NetworkResource::readData()
{
    QByteArray data;
    if (isFinishedWithNoError()) {
        data = reply()->readAll();
    }
    return data;
}

bool NetworkResource::saveData(const QString &path)
{
    if (isFinishedWithNoError()) {
        return qtlibs::File(path).writeData(reply()->readAll());
    }
    return false;
}

void NetworkResource::abort()
{
    if (reply()->isRunning()) {
        reply()->abort();
    }
}

void NetworkResource::replyFinished()
{
    if (isFinishedWithNoError()) {
        // Check if redirection
        // Note: An auto redirection option is available since Qt 5.6
        QUrl redirectUrl;
        if (reply()->hasRawHeader("Location")) {
            redirectUrl.setUrl(QString(reply()->rawHeader("Location")));
        }
        else if (reply()->hasRawHeader("Refresh")) {
            redirectUrl.setUrl(QString(reply()->rawHeader("Refresh")).split("url=").last());
        }
        if (!redirectUrl.isEmpty()) {
            if (redirectUrl.isRelative()) {
                redirectUrl = reply()->url().resolved(redirectUrl);
            }
            QNetworkRequest networkRequest = reply()->request();
            networkRequest.setUrl(redirectUrl);
            reply()->deleteLater();
            send(true, method(), networkRequest, formData());
            return;
        }
    }
    emit finished(this);
}

void NetworkResource::setManager(QNetworkAccessManager *manager)
{
    manager_ = manager;
}

void NetworkResource::setReply(QNetworkReply *reply)
{
    reply_ = reply;
}

void NetworkResource::setMethod(const QString &method)
{
    method_ = method;
}

void NetworkResource::setFormData(const QUrlQuery &formData)
{
    formData_ = formData;
}

NetworkResource *NetworkResource::send(bool async, const QString &method, const QNetworkRequest &request, const QUrlQuery &formData)
{
    setMethod(method);
    setFormData(formData);
    if (method == "HEAD") {
        setReply(manager()->head(request));
    }
    else if (method == "GET") {
        setReply(manager()->get(request));
        connect(reply(), &QNetworkReply::downloadProgress, this, &NetworkResource::downloadProgress);
    }
    else if (method == "POST") {
        setReply(manager()->post(request, formData.toString(QUrl::FullyEncoded).toUtf8()));
        connect(reply(), &QNetworkReply::uploadProgress, this, &NetworkResource::uploadProgress);
    }
    else if (method == "PUT") {
        setReply(manager()->put(request, formData.toString(QUrl::FullyEncoded).toUtf8()));
        connect(reply(), &QNetworkReply::uploadProgress, this, &NetworkResource::uploadProgress);
    }
    else if (method == "DELETE") {
        setReply(manager()->deleteResource(request));
    }
    else {
        Q_ASSERT(false);
    }
    connect(reply(), &QNetworkReply::finished, this, &NetworkResource::replyFinished);
    if (!async) {
        QEventLoop eventLoop;
        connect(this, &NetworkResource::finished, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();
    }
    return this;
}

} // namespace qtlibs
