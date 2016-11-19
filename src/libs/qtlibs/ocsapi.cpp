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

#include "ocsapi.h"

#include "json.h"
#include "networkresource.h"

namespace qtlibs {

OcsApi::OcsApi(const QUrl &baseUrl, QObject *parent)
    : QObject(parent), baseUrl_(baseUrl)
{}

OcsApi::OcsApi(const OcsApi &other, QObject *parent)
    : QObject(parent)
{
    setBaseUrl(other.baseUrl());
}

OcsApi &OcsApi::operator =(const OcsApi &other)
{
    setBaseUrl(other.baseUrl());
    return *this;
}

QUrl OcsApi::baseUrl() const
{
    return baseUrl_;
}

void OcsApi::setBaseUrl(const QUrl &baseUrl)
{
    baseUrl_ = baseUrl;
}

QJsonObject OcsApi::fetchCategories()
{
}

QJsonObject OcsApi::fetchProvidersFile(const QUrl &url)
{
}

} // namespace qtlibs
