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

class File : public QObject
{
    Q_OBJECT

public:
    explicit File(const QString &path = "", QObject *parent = nullptr);

    File(const File &other, QObject *parent = nullptr);
    File &operator =(const File &other);

    QString path() const;
    void setPath(const QString &path);

    bool exists() const;
    QByteArray readData() const;
    bool writeData(const QByteArray &data) const;
    QString readText() const;
    bool writeText(const QString &data) const;
    bool copy(const QString &newPath) const;
    bool move(const QString &newPath) const;
    bool remove() const;

private:
    QString path_;
};

}
