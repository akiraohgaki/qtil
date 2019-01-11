/**
 * Qtil
 *
 * @author      Akira Ohgaki <akiraohgaki@gmail.com>
 * @copyright   2016, Akira Ohgaki
 * @license     https://opensource.org/licenses/LGPL-3.0
 * @link        https://github.com/akiraohgaki/qtil
 */

#include "qtil_config.h"

#include "qtil_file.h"
#include "qtil_dir.h"
#include "qtil_json.h"

namespace Qtil {

Config::Config(const QString &configDirPath, QObject *parent)
    : QObject(parent), configDirPath_(configDirPath)
{}

Config::Config(const Config &other, QObject *parent)
    : QObject(parent)
{
    setConfigDirPath(other.configDirPath());
}

Config &Config::operator =(const Config &other)
{
    setConfigDirPath(other.configDirPath());
    return *this;
}

QString Config::configDirPath() const
{
    return configDirPath_;
}

void Config::setConfigDirPath(const QString &configDirPath)
{
    configDirPath_ = configDirPath;
}

QJsonObject Config::get(const QString &name) const
{
    auto configFilePath = configDirPath() + "/" + name + ".json";
    auto json = Qtil::File(configFilePath).readData();
    if (json.isEmpty()) {
        json = QString("{}").toUtf8(); // Blank JSON data as default
    }
    return Qtil::Json(json).toObject();
}

bool Config::set(const QString &name, const QJsonObject &object) const
{
    auto configFilePath = configDirPath() + "/" + name + ".json";
    auto json = Qtil::Json(object).toJson();
    Qtil::Dir(configDirPath()).make();
    return Qtil::File(configFilePath).writeData(json);
}

}
