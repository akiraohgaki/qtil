#include <QDebug>
#include <QCoreApplication>

#include "qtlibs/file.h"
#include "qtlibs/dir.h"
#include "qtlibs/json.h"
#include "qtlibs/config.h"
#include "qtlibs/networkresource.h"

#if defined(QTLIBS_UNIX)
#include "qtlibs/package.h"
#endif

#if defined(QTLIBS_ANDROID)
#include "qtlibs/android.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // testing ////////////////////////////////////////////

    qDebug() << "testing";

    // testing ////////////////////////////////////////////

    app.exit();
}
