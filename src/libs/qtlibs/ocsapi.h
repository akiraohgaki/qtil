/**
 * A library for Qt app
 *
 * LICENSE: The GNU Lesser General Public License, version 3.0
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0  The GNU Lesser General Public License, version 3.0
 * @link        https://github.com/akiraohgaki/qtlibs
 */

#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonObject>
#include <QJsonArray>

namespace qtlibs {

class OcsApi : public QObject
{
    Q_OBJECT

public:
    explicit OcsApi(const QUrl &baseUrl = QUrl(), QObject *parent = 0);

    OcsApi(const OcsApi &other, QObject *parent = 0);
    OcsApi &operator =(const OcsApi &other);

    QUrl baseUrl() const;
    void setBaseUrl(const QUrl &baseUrl);

    QJsonObject fetchContentCategories();

    static QJsonArray fetchProvidersFile(const QUrl &url);

private:
    QUrl baseUrl_;
};

} // namespace qtlibs
