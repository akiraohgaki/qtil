#include <QObject>
#include <QCoreApplication>
#include <QDebug>

#include "qtlibs/file.h"
#include "qtlibs/dir.h"
#include "qtlibs/json.h"
#include "qtlibs/config.h"
#include "qtlibs/networkresource.h"
#include "qtlibs/ocsapi.h"
#include "qtlibs/package.h"

class Test : public QObject
{
public:
    Test() {}
    virtual ~Test() {}

    void start() {
        qDebug() << "Start";

        qtlibs::NetworkResource *resource = new qtlibs::NetworkResource(
                    "LGPL-3.0",
                    QUrl("https://api.opensource.org/license/LGPL-3.0"),
                    false,
                    this);
        QJsonObject result = qtlibs::Json(resource->get()->readData()).toObject();

        qDebug() << resource->name() << ":" << result["name"].toString();

        resource->setUrl(QUrl(result["text"].toArray()[0].toObject()["url"].toString()));
        resource->setAsync(true);
        connect(resource, &qtlibs::NetworkResource::finished, this, &Test::finished);
        resource->get();
    }

public slots:
    void finished(qtlibs::NetworkResource *resource) {
        QString path = qtlibs::Dir::tempPath() + "/" + resource->url().fileName();
        resource->saveData(path);
        resource->deleteLater();

        qDebug() << "Downloaded :" << path;
        qDebug() << "Finished";

        QCoreApplication::exit();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Test test;
    test.start();

    return app.exec();
}
