#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T12:50:42
#
#-------------------------------------------------

QT       += core
QT       -= gui
QT       += sql

TARGET = qtserver
CONFIG   += console
CONFIG   -= app_bundle

#Enable c++11
CONFIG   += c++11

#Only include tests in the debug builds
debug {
    include(test/test.pri)
}

TEMPLATE = app


SOURCES += main.cpp \
    streamreader.cpp \
    streamwriter.cpp \
    jsonreader.cpp \
    jsonwriter.cpp

HEADERS += \
    streamreader.h \
    ichatmsg.h \
    ikeyvaluereader.h \
    ikeyvaluewriter.h \
    streamwriter.h \
    jsonreader.h \
    jsonwriter.h
