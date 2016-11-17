TARGET = qtlibs-test

TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += \
    src/app \
    src/libs

DISTFILES += README.txt

include(src/libs/qtlibs/qtlibs.pri)

include(src/app/app.pri)
