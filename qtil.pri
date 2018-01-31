CONFIG += c++11

QT += \
    core \
    network

HEADERS += \
    $${PWD}/src/qtil_file.h \
    $${PWD}/src/qtil_dir.h \
    $${PWD}/src/qtil_json.h \
    $${PWD}/src/qtil_config.h \
    $${PWD}/src/qtil_networkresource.h \
    $${PWD}/src/qtil_ocsapi.h \
    $${PWD}/src/qtil_package.h

SOURCES += \
    $${PWD}/src/qtil_file.cpp \
    $${PWD}/src/qtil_dir.cpp \
    $${PWD}/src/qtil_json.cpp \
    $${PWD}/src/qtil_config.cpp \
    $${PWD}/src/qtil_networkresource.cpp \
    $${PWD}/src/qtil_ocsapi.cpp \
    $${PWD}/src/qtil_package.cpp

INCLUDEPATH += $${PWD}/src

unix:!ios:!android {
    DEFINES += QTIL_OS_UNIX
}

android {
    QT += androidextras
}
