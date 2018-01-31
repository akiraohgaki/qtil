TARGET = qtil

TEMPLATE = lib

CONFIG += staticlib

DEFINES += QT_DEPRECATED_WARNINGS

DISTFILES += $${PWD}/README.md

include($${PWD}/qtil.pri)
