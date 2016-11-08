QT += \
    core \
    network

SOURCES += \
    $${PWD}/file.cpp \
    $${PWD}/dir.cpp \
    $${PWD}/json.cpp \
    $${PWD}/config.cpp \
    $${PWD}/network.cpp \
    $${PWD}/package.cpp

HEADERS += \
    $${PWD}/file.h \
    $${PWD}/dir.h \
    $${PWD}/json.h \
    $${PWD}/config.h \
    $${PWD}/network.h \
    $${PWD}/package.h

# Android
android {
    QT += androidextras

    SOURCES += $${PWD}/android.cpp

    HEADERS += $${PWD}/android.h
}
