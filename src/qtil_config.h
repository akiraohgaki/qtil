/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#pragma once

#include <QObject>
#include <QJsonObject>

namespace Qtil {

class Config : public QObject
{
    Q_OBJECT

public:
    explicit Config(const QString &configDirPath = QString(), QObject *parent = nullptr);

    Config(const Config &other, QObject *parent = nullptr);
    Config &operator =(const Config &other);

    QString configDirPath() const;
    void setConfigDirPath(const QString &configDirPath);

    QJsonObject get(const QString &name) const;
    bool set(const QString &name, const QJsonObject &object) const;

private:
    QString configDirPath_;
};

}
