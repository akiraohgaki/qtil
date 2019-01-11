/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#include "qtil_ocsapi.h"

#include <QXmlStreamReader>

#include "qtil_json.h"
#include "qtil_networkresource.h"

namespace Qtil {

// OCS-API Specification
// https://www.freedesktop.org/wiki/Specifications/open-collaboration-services/

OcsApi::OcsApi(const QString &id, const QUrl &baseUrl, const QString &userName, const QString &password, QObject *parent)
    : QObject(parent), id_(id), baseUrl_(baseUrl), userName_(userName), password_(password)
{}

OcsApi::OcsApi(const OcsApi &other, QObject *parent)
    : QObject(parent)
{
    setId(other.id());
    setBaseUrl(other.baseUrl());
    setUserName(other.userName());
    setPassword(other.password());
}

OcsApi &OcsApi::operator =(const OcsApi &other)
{
    setId(other.id());
    setBaseUrl(other.baseUrl());
    setUserName(other.userName());
    setPassword(other.password());
    return *this;
}

QString OcsApi::id() const
{
    return id_;
}

void OcsApi::setId(const QString &id)
{
    id_ = id;
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

QJsonObject OcsApi::getConfig() const
{
    auto url = baseUrl().resolved(QUrl("config"));
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::checkPerson() const
{
    auto url = baseUrl().resolved(QUrl("person/check"));
    QUrlQuery formData;
    formData.addQueryItem("login", userName());
    formData.addQueryItem("password", password());
    formData.addQueryItem("format", "json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.post(formData)->readData()).toObject();
}

QJsonObject OcsApi::getPersonDataSet(const QUrlQuery &query) const
{
    auto url = baseUrl().resolved(QUrl("person/data"));
    url.setUserName(userName());
    url.setPassword(password());
    auto newQuery = query;
    newQuery.removeQueryItem("format");
    newQuery.addQueryItem("format", "json");
    url.setQuery(newQuery);
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getPersonData(const QString &personId) const
{
    auto url = baseUrl().resolved(QUrl("person/data/" + personId));
    url.setUserName(userName());
    url.setPassword(password());
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getPersonSelf() const
{
    auto url = baseUrl().resolved(QUrl("person/self"));
    url.setUserName(userName());
    url.setPassword(password());
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentCategories() const
{
    auto url = baseUrl().resolved(QUrl("content/categories"));
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentDataSet(const QUrlQuery &query) const
{
    auto url = baseUrl().resolved(QUrl("content/data"));
    auto newQuery = query;
    newQuery.removeQueryItem("format");
    newQuery.addQueryItem("format", "json");
    url.setQuery(newQuery);
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentData(const QString &contentId) const
{
    auto url = baseUrl().resolved(QUrl("content/data/" + contentId));
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonObject OcsApi::getContentDownload(const QString &contentId, const QString &itemId) const
{
    auto url = baseUrl().resolved(QUrl("content/download/" + contentId + "/" + itemId));
    url.setQuery("format=json");
    Qtil::NetworkResource resource(url.toString(), url, false);
    return Qtil::Json(resource.get()->readData()).toObject();
}

QJsonArray OcsApi::getProviderFile(const QUrl &url)
{
    QJsonArray providers;
    Qtil::NetworkResource resource(url.toString(), url, false);
    QXmlStreamReader reader(resource.get()->readData());
    QStringList whitelist{"id", "location", "name", "icon", "termsofuse", "register"};
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if (reader.isStartElement() && reader.name() == "provider") {
            QJsonObject provider;
            provider["_providerfile"] = url.toString();
            providers.append(provider);
            continue;
        }
        auto elementName = reader.name().toString();
        if (!providers.isEmpty() && whitelist.contains(elementName)) {
            auto i = providers.size() - 1;
            auto provider = providers[i].toObject();
            provider[elementName] = reader.readElementText();
            providers[i] = provider;
        }
    }
    return providers;
}

}
