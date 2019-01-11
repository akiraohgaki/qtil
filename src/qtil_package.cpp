/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#include "qtil_package.h"

#ifdef QTIL_OS_UNIX
#include <QJsonObject>
#include <QMimeDatabase>
#include <QProcess>
#endif

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

namespace Qtil {

Package::Package(const QString &path, QObject *parent)
    : QObject(parent), path_(path)
{}

Package::Package(const Package &other, QObject *parent)
    : QObject(parent)
{
    setPath(other.path());
}

Package &Package::operator =(const Package &other)
{
    setPath(other.path());
    return *this;
}

QString Package::path() const
{
    return path_;
}

void Package::setPath(const QString &path)
{
    path_ = path;
}

#ifdef QTIL_OS_UNIX
bool Package::installAsProgram(const QString &newPath) const
{
    QStringList arguments{"-m", "755", "-p", path(), newPath};
    return execute("install", arguments);
}

bool Package::installAsFile(const QString &newPath) const
{
    QStringList arguments{"-m", "644", "-p", path(), newPath};
    return execute("install", arguments);
}

bool Package::installAsArchive(const QString &destinationDirPath) const
{
    QJsonObject archiveTypes;
    archiveTypes["application/x-tar"] = QString("tar");
    archiveTypes["application/x-gzip"] = QString("tar");
    archiveTypes["application/gzip"] = QString("tar");
    archiveTypes["application/x-bzip"] = QString("tar");
    archiveTypes["application/x-bzip2"] = QString("tar");
    archiveTypes["application/x-xz"] = QString("tar");
    archiveTypes["application/x-lzma"] = QString("tar");
    archiveTypes["application/x-lzip"] = QString("tar");
    archiveTypes["application/x-compressed-tar"] = QString("tar");
    archiveTypes["application/x-bzip-compressed-tar"] = QString("tar");
    archiveTypes["application/x-bzip2-compressed-tar"] = QString("tar");
    archiveTypes["application/x-xz-compressed-tar"] = QString("tar");
    archiveTypes["application/x-lzma-compressed-tar"] = QString("tar");
    archiveTypes["application/x-lzip-compressed-tar"] = QString("tar");
    archiveTypes["application/zip"] = QString("zip");
    archiveTypes["application/x-7z-compressed"] = QString("7z");
    archiveTypes["application/x-rar"] = QString("rar");
    archiveTypes["application/x-rar-compressed"] = QString("rar");

    auto mimeType = QMimeDatabase().mimeTypeForFile(path()).name();

    if (archiveTypes.contains(mimeType)) {
        auto archiveType = archiveTypes[mimeType].toString();

        QStringList tarArguments{"-xf", path(), "-C", destinationDirPath};
        QStringList unzipArguments{"-o", path(), "-d", destinationDirPath};
        QStringList sevenzArguments{"x", path(), "-o" + destinationDirPath}; // No space between -o and directory
        QStringList unrarArguments{"e", path(), destinationDirPath};
        QStringList unarArguments{"-f", path(), "-o", destinationDirPath};

        if (archiveType == "tar" && execute("tar", tarArguments)) {
            return true;
        }
        else if (archiveType == "zip" && execute("unzip", unzipArguments)) {
            return true;
        }
        else if (archiveType == "7z" && (execute("7z", sevenzArguments) || execute("7zr", sevenzArguments))) {
            return true;
        }
        else if (archiveType == "rar" && execute("unrar", unrarArguments)) {
            return true;
        }
        // Those suitable unarchiver may not installed, try with unar
        return execute("unar", unarArguments);
    }
    return false;
}

bool Package::installAsPlasmapkg(const QString &type) const
{
    QStringList arguments{"-t", type, "-i", path()};
    return execute("plasmapkg2", arguments);
}

bool Package::uninstallAsPlasmapkg(const QString &type) const
{
    QStringList arguments{"-t", type, "-r", path()};
    return execute("plasmapkg2", arguments);
}
#endif

#ifdef Q_OS_ANDROID
bool Package::installAsApk() const
{
    auto activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (activity.isValid()) {
        auto filePath = path();
        if (filePath.startsWith("file://", Qt::CaseInsensitive)) {
            filePath.replace("file://localhost", "", Qt::CaseInsensitive);
            filePath.replace("file://", "", Qt::CaseInsensitive);
        }

        auto fileUri = QAndroidJniObject::fromString("file://" + filePath);
        auto uri = QAndroidJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", fileUri.object());
        auto mimeType = QAndroidJniObject::fromString("application/vnd.android.package-archive");

        auto ACTION_VIEW = QAndroidJniObject::getStaticObjectField("android/content/Intent", "ACTION_VIEW", "Ljava/lang/String");
        auto FLAG_ACTIVITY_NEW_TASK = QAndroidJniObject::getStaticObjectField("android/content/Intent", "FLAG_ACTIVITY_NEW_TASK", "Ljava/lang/Integer");

        QAndroidJniObject intent("android/content/Intent", "(Ljava/lang/String;)V", ACTION_VIEW.object());
        intent = intent.callObjectMethod("setDataAndType", "(Landroid/net/Uri;Ljava/lang/String;)Landroid/content/Intent;", uri.object(), mimeType.object());
        intent = intent.callObjectMethod("setFlags", "(I)Landroid/content/Intent;", FLAG_ACTIVITY_NEW_TASK.object());

        activity.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", intent.object());
        return true;
    }
    return false;
}
#endif

#ifdef QTIL_OS_UNIX
bool Package::execute(const QString &program, const QStringList &arguments) const
{
    QProcess process;
    process.start(program, arguments);
    if (process.waitForFinished()) {
        process.waitForReadyRead();
        return true;
    }
    return false;
}
#endif

}
