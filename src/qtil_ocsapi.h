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
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>

namespace Qtil {

class OcsApi : public QObject
{
    Q_OBJECT

public:
    explicit OcsApi(const QString &id = QString(), const QUrl &baseUrl = QUrl(), const QString &userName = QString(), const QString &password = QString(), QObject *parent = nullptr);

    OcsApi(const OcsApi &other, QObject *parent = nullptr);
    OcsApi &operator =(const OcsApi &other);

    QString id() const;
    void setId(const QString &id);
    QUrl baseUrl() const;
    void setBaseUrl(const QUrl &baseUrl);
    QString userName() const;
    void setUserName(const QString &userName);
    QString password() const;
    void setPassword(const QString &password);

    QJsonObject getConfig() const;
    QJsonObject checkPerson() const;
    QJsonObject getPersonDataSet(const QUrlQuery &query = QUrlQuery()) const;
    QJsonObject getPersonData(const QString &personId) const;
    QJsonObject getPersonSelf() const;
    QJsonObject getContentCategories() const;
    QJsonObject getContentDataSet(const QUrlQuery &query = QUrlQuery()) const;
    QJsonObject getContentData(const QString &contentId) const;
    QJsonObject getContentDownload(const QString &contentId, const QString &itemId) const;

    static QJsonArray getProviderFile(const QUrl &url);

private:
    QString id_;
    QUrl baseUrl_;
    QString userName_;
    QString password_;
};

}
