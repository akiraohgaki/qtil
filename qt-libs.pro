TARGET = qt-libs

TEMPLATE = lib

QT += \
    core \
    network

CONFIG += c++11

SOURCES += \
    src/libs/utils/config.cpp \
    src/libs/utils/network.cpp \
    src/libs/utils/file.cpp \
    src/libs/utils/json.cpp \
    src/libs/utils/package.cpp

HEADERS += \
    src/libs/utils/config.h \
    src/libs/utils/network.h \
    src/libs/utils/file.h \
    src/libs/utils/json.h \
    src/libs/utils/package.h

DISTFILES += README.txt

# Android
android {
    QT += androidextras

    SOURCES += src/libs/utils/android.cpp

    HEADERS += src/libs/utils/android.h
}
