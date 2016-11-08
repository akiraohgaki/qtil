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

#include "network.h"

#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace utils {

Network::Network(const bool &async, QObject *parent) :
    QObject(parent), async_(async)
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this, &Network::finished);
    if (!async_) {
        eventLoop_ = new QEventLoop();
        connect(manager_, &QNetworkAccessManager::finished, eventLoop_, &QEventLoop::quit);
    }
}

Network::~Network()
{
    manager_->deleteLater();
    if (!async_) {
        delete eventLoop_;
    }
}

QUrl Network::url() const
{
    return url_;
}

void Network::setUrl(const QUrl &url)
{
    url_ = url;
}

QNetworkReply *Network::head(const QUrl &uri)
{
    QNetworkReply *reply = manager_->head(QNetworkRequest(uri));
    if (!async_) {
        eventLoop_->exec();
    }
    return reply;
}

QNetworkReply *Network::get(const QUrl &uri)
{
    QNetworkReply *reply = manager_->get(QNetworkRequest(uri));
    connect(reply, &QNetworkReply::downloadProgress, this, &Network::downloadProgress);
    if (!async_) {
        eventLoop_->exec();
    }
    return reply;
}

} // namespace utils
