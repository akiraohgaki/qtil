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

#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

namespace utils {

class Json : public QObject
{
    Q_OBJECT

public:
    explicit Json(const QString &json, QObject *parent = 0);
    explicit Json(const QJsonObject &object, QObject *parent = 0);
    explicit Json(const QJsonArray &array, QObject *parent = 0);

    QString json() const;
    void setJson(const QString &json);

    bool isValid();
    bool isObject();
    bool isArray();
    QString toJson();
    QJsonObject toObject();
    QJsonArray toArray();

private:
    QString json_;
};

} // namespace utils
