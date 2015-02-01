#-------------------------------------------------
#
# Project created by QtCreator 2015-01-31T10:17:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UdpPortsEchoServer
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
		mainwindow.cpp\
		udplistener.cpp

HEADERS  += mainwindow.h\
		 udplistener.h

FORMS    += mainwindow.ui

OTHER_FILES += README.md\
			.gitignore\
			LICENSE
