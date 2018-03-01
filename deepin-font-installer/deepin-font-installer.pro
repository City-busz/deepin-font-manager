######################################################################
# Automatically generated by qmake (3.0) ?? 12? 20 11:40:37 2017
######################################################################

QT += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = deepin-font-installer

CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget freetype2 fontconfig

INCLUDEPATH += $$PWD/../libdeepin-font-installer
LIBS += -L$$OUT_PWD/../libdeepin-font-installer -ldeepin-font-installer
DEFINES += QT_MESSAGELOGCONTEXT

# Input
HEADERS += homepage.h \
           listview.h \
	   listitem.h \
	   mainwindow.h \
	   multifilepage.h \
	   singlefilepage.h \
	   utils.h \
	   progress.h \
	   refreshthread.h

SOURCES += homepage.cpp \
           listview.cpp \
	   listitem.cpp \
	   main.cpp \
	   mainwindow.cpp \
	   multifilepage.cpp \
	   singlefilepage.cpp \
	   utils.cpp \
	   progress.cpp \
	   refreshthread.cpp

RESOURCES += deepin-font-installer.qrc
TRANSLATIONS += translations/deepin-font-installer.ts

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications
isEmpty(DSRDIR):DSRDIR=/usr/share/deepin-font-installer

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = $$PWD/../deepin-font-installer.desktop

policy.path = /usr/share/polkit-1/actions
policy.files = com.deepin.pkexec.font-install.policy \
               com.deepin.pkexec.font-uninstall.policy \
               com.deepin.pkexec.font-reinstall.policy

# Automating generation .qm files from .ts files
!system($$PWD/translations/translate_generation.sh): error("Failed to generate translation")

translations.path = /usr/share/deepin-font-installer/translations
translations.files = $$PWD/translations/*.qm

icon_files.path = /usr/share/icons/hicolor/scalable/apps
icon_files.files = $$PWD/images/deepin-font-installer.svg

manual.path = /usr/share/dman/deepin-font-installer
manual.files = $$PWD/dman/*

INSTALLS += target desktop policy translations icon_files manual