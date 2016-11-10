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

#include "config.h"

#include "file.h"
#include "dir.h"
#include "json.h"

namespace qtlibs {

Config::Config(const QString &configDirPath, QObject *parent) :
    QObject(parent), configDirPath_(configDirPath)
{}

QString Config::configDirPath() const
{
    return configDirPath_;
}

void Config::setConfigDirPath(const QString &configDirPath)
{
    configDirPath_ = configDirPath;
}

QJsonObject Config::get(const QString &name)
{
    QString configFilePath = configDirPath() + "/" + name + ".json";
    QString json = qtlibs::File(configFilePath).readText();
    if (json.isEmpty()) {
        json = "{}"; // Blank JSON data as default
    }
    return qtlibs::Json(json).toObject();
}

bool Config::set(const QString &name, const QJsonObject &object)
{
    QString configFilePath = configDirPath() + "/" + name + ".json";
    QString json = qtlibs::Json(object).toJson();
    qtlibs::Dir(configDirPath()).make();
    if (qtlibs::File(configFilePath).writeText(json)) {
        return true;
    }
    return false;
}

} // namespace qtlibs
