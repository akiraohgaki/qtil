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

namespace qtlib {

class Package : public QObject
{
    Q_OBJECT

public:
    explicit Package(const QString &path = "", QObject *parent = nullptr);

    Package(const Package &other, QObject *parent = nullptr);
    Package &operator =(const Package &other);

    QString path() const;
    void setPath(const QString &path);

#ifdef QTLIB_UNIX
    bool installAsProgram(const QString &newPath) const;
    bool installAsFile(const QString &newPath) const;
    bool installAsArchive(const QString &destinationDirPath) const;
    bool installAsPlasmapkg(const QString &type = "plasmoid") const;
    bool uninstallAsPlasmapkg(const QString &type = "plasmoid") const;
#endif

#ifdef Q_OS_ANDROID
    bool installAsApk() const;
#endif

private:
#ifdef QTLIB_UNIX
    bool execute(const QString &program, const QStringList &arguments) const;
#endif

    QString path_;
};

}
