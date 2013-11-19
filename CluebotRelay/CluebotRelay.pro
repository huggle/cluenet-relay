#-------------------------------------------------
#
# Project created by QtCreator 2013-11-19T12:59:33
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = CluebotRelay
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    networkirc.cpp \
    cluebotrelay.cpp

HEADERS += \
    networkirc.hpp \
    cluebotrelay.hpp
