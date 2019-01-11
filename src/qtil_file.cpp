/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#include "qtil_file.h"

#include <QIODevice>
#include <QTextStream>
#include <QFile>

namespace Qtil {

File::File(const QString &path, QObject *parent)
    : QObject(parent), path_(path)
{}

File::File(const File &other, QObject *parent)
    : QObject(parent)
{
    setPath(other.path());
}

File &File::operator =(const File &other)
{
    setPath(other.path());
    return *this;
}

QString File::path() const
{
    return path_;
}

void File::setPath(const QString &path)
{
    path_ = path;
}

bool File::exists() const
{
    return QFile(path()).exists();
}

QByteArray File::readData() const
{
    QByteArray data;
    QFile file(path());
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        data = file.readAll();
        file.close();
    }
    return data;
}

bool File::writeData(const QByteArray &data) const
{
    QFile file(path());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(data);
        file.close();
        return true;
    }
    return false;
}

QString File::readText() const
{
    QString data;
    QFile file(path());
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        data = in.readAll();
        file.close();
    }
    return data;
}

bool File::writeText(const QString &data) const
{
    QFile file(path());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << data;
        file.close();
        return true;
    }
    return false;
}

bool File::copy(const QString &newPath) const
{
    return QFile(path()).copy(newPath);
}

bool File::move(const QString &newPath) const
{
    return QFile(path()).rename(newPath);
}

bool File::remove() const
{
    return QFile(path()).remove();
}

}
