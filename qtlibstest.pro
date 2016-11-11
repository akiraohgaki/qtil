TARGET = qtlibstest

TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += \
    src/app \
    src/libs

DISTFILES += README.txt

include(src/app/app.pri)

include(src/libs/qtlibs/qtlibs.pri)
