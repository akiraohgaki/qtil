QT += \
    core \
    network

HEADERS += \
    $${PWD}/file.h \
    $${PWD}/dir.h \
    $${PWD}/json.h \
    $${PWD}/config.h \
    $${PWD}/networkresource.h

SOURCES += \
    $${PWD}/file.cpp \
    $${PWD}/dir.cpp \
    $${PWD}/json.cpp \
    $${PWD}/config.cpp \
    $${PWD}/networkresource.cpp

# Unix
unix:!ios:!android {
    HEADERS += $${PWD}/package.h
    SOURCES += $${PWD}/package.cpp
    DEFINES += QTLIBS_UNIX
}

# Android
android {
    QT += androidextras
    HEADERS += $${PWD}/android.h
    SOURCES += $${PWD}/android.cpp
    DEFINES += QTLIBS_ANDROID
}
