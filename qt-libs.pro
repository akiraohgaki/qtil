TARGET = qt-libs

TEMPLATE = lib

QT += \
    core \
    network

CONFIG += c++11

SOURCES += \
    $${PWD}/src/libs/utils/config.cpp \
    $${PWD}/src/libs/utils/network.cpp \
    $${PWD}/src/libs/utils/file.cpp \
    $${PWD}/src/libs/utils/json.cpp \
    $${PWD}/src/libs/utils/package.cpp

HEADERS += \
    $${PWD}/src/libs/utils/config.h \
    $${PWD}/src/libs/utils/network.h \
    $${PWD}/src/libs/utils/file.h \
    $${PWD}/src/libs/utils/json.h \
    $${PWD}/src/libs/utils/package.h

DISTFILES += $${PWD}/README.txt

# Android
android {
    QT += androidextras

    SOURCES += $${PWD}/src/libs/utils/android.cpp

    HEADERS += $${PWD}/src/libs/utils/android.h
}
