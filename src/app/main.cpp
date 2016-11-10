#include <QDebug>
#include <QCoreApplication>

#include "utils/file.h"
#include "utils/dir.h"
#include "utils/json.h"
#include "utils/config.h"
#include "utils/networkresource.h"

#if defined(Q_OS_UNIX) && !defined(Q_OS_IOS) && !defined(Q_OS_ANDROID)
#include "utils/package.h"
#endif

#if defined(Q_OS_ANDROID)
#include "utils/android.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // testing ////////////////////////////////////////////

    qDebug() << "testing";

    // testing ////////////////////////////////////////////

    app.exit();
}
