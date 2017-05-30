/**
 * qtlib
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtlib
 */

#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

namespace qtlib {

class Json : public QObject
{
    Q_OBJECT

public:
    explicit Json(const QByteArray &json = QByteArray(), QObject *parent = nullptr);
    explicit Json(const QJsonObject &object, QObject *parent = nullptr);
    explicit Json(const QJsonArray &array, QObject *parent = nullptr);

    Json(const Json &other, QObject *parent = nullptr);
    Json &operator =(const Json &other);

    QByteArray json() const;
    void setJson(const QByteArray &json);

    void fromObject(const QJsonObject &object);
    void fromArray(const QJsonArray &array);
    QByteArray toJson() const;
    QJsonObject toObject() const;
    QJsonArray toArray() const;
    bool isValid() const;
    bool isObject() const;
    bool isArray() const;

private:
    QByteArray json_;
};

}
