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

#include "config.h"

#include "file.h"
#include "dir.h"
#include "json.h"

namespace utils {

Config::Config(const QString &configDir, QObject *parent) :
    QObject(parent), configDir_(configDir)
{}

QString Config::configDir() const
{
    return configDir_;
}

void Config::setConfigDir(const QString &configDir)
{
    configDir_ = configDir;
}

QJsonObject Config::get(const QString &name)
{
    QString configFile = configDir() + "/" + name + ".json";
    if (!cacheData_.contains(name)) {
        QString json = utils::File(configFile).readText();
        if (json.isEmpty()) {
            json = "{}"; // Blank JSON data as default
        }
        cacheData_[name] = utils::Json(json).toObject();
    }
    return cacheData_[name].toObject();
}

bool Config::set(const QString &name, const QJsonObject &object)
{
    QString configFile = configDir() + "/" + name + ".json";
    QString json = utils::Json(object).toJson();
    utils::Dir(configDir()).make();
    if (utils::File(configFile).writeText(json)) {
        cacheData_[name] = object;
        return true;
    }
    return false;
}

} // namespace utils
