CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(snlineeditplugin)
TEMPLATE    = lib

HEADERS     = snlineeditplugin.h
SOURCES     = snlineeditplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

message(target.path)
include(snlineedit.pri)
