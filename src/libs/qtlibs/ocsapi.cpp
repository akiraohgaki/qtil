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

#include "ocsapi.h"

#include <QXmlStreamReader>

#include "json.h"
#include "networkresource.h"

namespace qtlibs {

// OCS-API Specification
// https://www.freedesktop.org/wiki/Specifications/open-collaboration-services/

OcsApi::OcsApi(const QUrl &baseUrl, const QString &userName, const QString &password, QObject *parent)
    : QObject(parent), baseUrl_(baseUrl), userName_(userName), password_(password)
{}

OcsApi::OcsApi(const OcsApi &other, QObject *parent)
    : QObject(parent)
{
    setBaseUrl(other.baseUrl());
    setUserName(other.userName());
    setPassword(other.password());
}

OcsApi &OcsApi::operator =(const OcsApi &other)
{
    setBaseUrl(other.baseUrl());
    setUserName(other.userName());
    setPassword(other.password());
    return *this;
}

QUrl OcsApi::baseUrl() const
{
    return baseUrl_;
}

void OcsApi::setBaseUrl(const QUrl &baseUrl)
{
    baseUrl_ = baseUrl;
}

QString OcsApi::userName() const
{
    return userName_;
}

void OcsApi::setUserName(const QString &userName)
{
    userName_ = userName;
}

QString OcsApi::password() const
{
    return password_;
}

void OcsApi::setPassword(const QString &password)
{
    password_ = password;
}

QJsonObject OcsApi::getConfig()
{
    QUrl url = baseUrl().resolved(QUrl("config"));
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::checkPerson()
{
    QUrl url = baseUrl().resolved(QUrl("person/check"));
    QUrlQuery formData;
    formData.addQueryItem("login", userName());
    formData.addQueryItem("password", password());
    formData.addQueryItem("format", "json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.post(formData)->readData()).toObject();
}

QJsonObject OcsApi::getPersonDataSet(const QUrlQuery &query)
{
    QUrl url = baseUrl().resolved(QUrl("person/data"));
    url.setUserName(userName());
    url.setPassword(password());
    QUrlQuery newQuery(query);
    newQuery.removeQueryItem("format");
    newQuery.addQueryItem("format", "json");
    url.setQuery(newQuery);
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getPersonData(const QString &personId)
{
    QUrl url = baseUrl().resolved(QUrl("person/data/" + personId));
    url.setUserName(userName());
    url.setPassword(password());
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getPersonSelf()
{
    QUrl url = baseUrl().resolved(QUrl("person/self"));
    url.setUserName(userName());
    url.setPassword(password());
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentCategories()
{
    QUrl url = baseUrl().resolved(QUrl("content/categories"));
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentDataSet(const QUrlQuery &query)
{
    QUrl url = baseUrl().resolved(QUrl("content/data"));
    QUrlQuery newQuery(query);
    newQuery.removeQueryItem("format");
    newQuery.addQueryItem("format", "json");
    url.setQuery(newQuery);
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentData(const QString &contentId)
{
    QUrl url = baseUrl().resolved(QUrl("content/data/" + contentId));
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentDownload(const QString &contentId, const QString &itemId)
{
    QUrl url = baseUrl().resolved(QUrl("content/download/" + contentId + "/" + itemId));
    url.setQuery("format=json");
    qtlibs::NetworkResource resource(url.toString(), url, false);
    return qtlibs::Json(resource.get()->readData()).toObject();
}

QJsonArray OcsApi::getProviderFile(const QUrl &url)
{
    QJsonArray providers;
    qtlibs::NetworkResource resource(url.toString(), url, false);
    QXmlStreamReader reader(resource.get()->readData());
    QStringList whitelist;
    whitelist << "id" << "location" << "name" << "icon" << "termsofuse" << "register";
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if (reader.isStartElement() && reader.name() == "provider") {
            QJsonObject provider;
            provider["_providers_file"] = url.toString();
            providers.append(provider);
            continue;
        }
        QString elementName = reader.name().toString();
        if (!providers.isEmpty() && whitelist.contains(elementName)) {
            int i(providers.size() - 1);
            QJsonObject provider = providers[i].toObject();
            provider[elementName] = reader.readElementText();
            providers[i] = provider;
        }
    }
    return providers;
}

} // namespace qtlibs
