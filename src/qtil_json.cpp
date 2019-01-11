/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#include "qtil_json.h"

#include <QJsonDocument>
#include <QJsonParseError>

namespace Qtil {

Json::Json(const QByteArray &json, QObject *parent)
    : QObject(parent), json_(json)
{}

Json::Json(const QJsonObject &object, QObject *parent)
    : QObject(parent)
{
    fromObject(object);
}

Json::Json(const QJsonArray &array, QObject *parent)
    : QObject(parent)
{
    fromArray(array);
}

Json::Json(const Json &other, QObject *parent)
    : QObject(parent)
{
    setJson(other.json());
}

Json &Json::operator =(const Json &other)
{
    setJson(other.json());
    return *this;
}

QByteArray Json::json() const
{
    return json_;
}

void Json::setJson(const QByteArray &json)
{
    json_ = json;
}

void Json::fromObject(const QJsonObject &object)
{
    setJson(QJsonDocument(object).toJson());
}

void Json::fromArray(const QJsonArray &array)
{
    setJson(QJsonDocument(array).toJson());
}

QByteArray Json::toJson() const
{
    return QJsonDocument::fromJson(json()).toJson();
}

QJsonObject Json::toObject() const
{
    return QJsonDocument::fromJson(json()).object();
}

QJsonArray Json::toArray() const
{
    return QJsonDocument::fromJson(json()).array();
}

bool Json::isValid() const
{
    QJsonParseError parseError;
    QJsonDocument::fromJson(json(), &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        return true;
    }
    return false;
}

bool Json::isObject() const
{
    return QJsonDocument::fromJson(json()).isObject();
}

bool Json::isArray() const
{
    return QJsonDocument::fromJson(json()).isArray();
}

}
