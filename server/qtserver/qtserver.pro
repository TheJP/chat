#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T12:50:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qtserver
CONFIG   += console
CONFIG   -= app_bundle

#Try
CONFIG   += c++11

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
