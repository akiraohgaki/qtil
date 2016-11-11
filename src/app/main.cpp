#include <QDebug>
#include <QCoreApplication>

#include "qtlibs/file.h"
#include "qtlibs/dir.h"
#include "qtlibs/json.h"
#include "qtlibs/config.h"
#include "qtlibs/networkresource.h"
#include "qtlibs/package.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // testing ////////////////////////////////////////////

    qDebug() << "testing";

    // testing ////////////////////////////////////////////

    app.exit();
}
