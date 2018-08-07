#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T11:20:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rdesker
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	mdbQtStd/debug.cpp \
	mdbQtStd/mdbQtStd.cpp \
	mdbQtStd/mdstatebar.cpp \
	mdbQtStd/types.cpp \
	locals.cpp \
    myclass.cpp

HEADERS  += mainwindow.h \
	mdbQtStd/debug.h \
	mdbQtStd/mdstatebar.h \
	mdbQtStd/mdbQtStd.h \
	mdbQtStd/types.h \
	locals.h \
    myclass.h

FORMS    += mainwindow.ui

RESOURCES += \
	rdesker.qrc

DISTFILES += \
	images/textedit_res/logo32.png \
	images/bigPencilNote.png \
	images/down_arrowb.png \
	images/notesBlackPencil.png \
	images/up_arrowb.png \
	images/greenCheck.xcf \
	rdesker \
	README.md
