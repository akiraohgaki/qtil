/**
 * A library for Qt app
 *
 * LICENSE: The GNU Lesser General Public License, version 3.0
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0  The GNU Lesser General Public License, version 3.0
 * @link        https://github.com/akiraohgaki/qt-libs
 */

#include "json.h"

#include <QJsonDocument>
#include <QJsonParseError>

namespace utils {

Json::Json(const QString &json, QObject *parent) :
    QObject(parent), json_(json)
{}

Json::Json(const QJsonObject &object, QObject *parent) :
    QObject(parent)
{
    QJsonDocument doc(object);
    setJson(QString::fromUtf8(doc.toJson()));
}

Json::Json(const QJsonArray &array, QObject *parent) :
    QObject(parent)
{
    QJsonDocument doc(array);
    setJson(QString::fromUtf8(doc.toJson()));
}

QString Json::json() const
{
    return json_;
}

void Json::setJson(const QString &json)
{
    json_ = json;
}

bool Json::isValid()
{
    QJsonParseError parseError;
    QJsonDocument::fromJson(json().toUtf8(), &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        return true;
    }
    return false;
}

bool Json::isObject()
{
    QJsonDocument doc = QJsonDocument::fromJson(json().toUtf8());
    return doc.isObject();
}

bool Json::isArray()
{
    QJsonDocument doc = QJsonDocument::fromJson(json().toUtf8());
    return doc.isArray();
}

QString Json::toJson()
{
    QJsonDocument doc = QJsonDocument::fromJson(json().toUtf8());
    return QString::fromUtf8(doc.toJson());
}

QJsonObject Json::toObject()
{
    QJsonDocument doc = QJsonDocument::fromJson(json().toUtf8());
    return doc.object();
}

QJsonArray Json::toArray()
{
    QJsonDocument doc = QJsonDocument::fromJson(json().toUtf8());
    return doc.array();
}

} // namespace utils
