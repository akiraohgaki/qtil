DISTFILES += README.txt

INCLUDEPATH += \
    src/app \
    src/libs

include(src/app/app.pri)

include(src/libs/utils/utils.pri)
