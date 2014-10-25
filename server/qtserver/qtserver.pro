#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T12:50:42
#
#-------------------------------------------------

QT += core
QT -= gui
QT += sql
QT += websockets

TARGET = qtserver
CONFIG   += console
CONFIG   -= app_bundle

#Enable c++11
CONFIG   += c++11

#include subprojects
include(msgs/msgs.pri)
include(services/services.pri)
include(streamable/streamable.pri)

#Only include tests in the debug builds
debug {
    include(test/test.pri)
}

TEMPLATE = app


SOURCES += main.cpp \
    streamreader.cpp \
    streamwriter.cpp \
    jsonreader.cpp \
    jsonwriter.cpp \
    server.cpp \
    protocol.cpp \
    notificationsender.cpp \
    jsonformat.cpp

HEADERS += \
    streamreader.h \
    ichatmsg.h \
    ikeyvaluereader.h \
    ikeyvaluewriter.h \
    streamwriter.h \
    jsonreader.h \
    jsonwriter.h \
    server.h \
    protocol.h \
    notificationsender.h \
    iformat.h \
    jsonformat.h \
    istreamable.h

OTHER_FILES +=
