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

namespace Qtil {

class Package : public QObject
{
    Q_OBJECT

public:
    explicit Package(const QString &path = QString(), QObject *parent = nullptr);

    Package(const Package &other, QObject *parent = nullptr);
    Package &operator =(const Package &other);

    QString path() const;
    void setPath(const QString &path);

#ifdef QTIL_OS_UNIX
    bool installAsProgram(const QString &newPath) const;
    bool installAsFile(const QString &newPath) const;
    bool installAsArchive(const QString &destinationDirPath) const;
    bool installAsPlasmapkg(const QString &type = QString("plasmoid")) const;
    bool uninstallAsPlasmapkg(const QString &type = QString("plasmoid")) const;
#endif

#ifdef Q_OS_ANDROID
    bool installAsApk() const;
#endif

private:
#ifdef QTIL_OS_UNIX
    bool execute(const QString &program, const QStringList &arguments) const;
#endif

    QString path_;
};

}
