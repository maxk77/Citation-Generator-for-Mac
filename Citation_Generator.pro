#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T16:25:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Citation_Generator
TEMPLATE = app
ICON = icon.icns
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    navigation_page.cpp \
    book_page.cpp \
    web_page.cpp \
    journal_page.cpp \
    apa_guidance_page.cpp \
    mla_guidance_page.cpp \
    newspaper.cpp \
    magazine_page.cpp


HEADERS += \
    navigation_page.h \
    book_page.h \
    web_page.h \
    journal_page.h \
    utils.h \
    apa_guidance_page.h \
    mla_guidance_page.h \
    newspaper.h \
    magazine_page.h


FORMS += \
    navigation_page.ui \
    book_page.ui \
    web_page.ui \
    journal_page.ui \
    apa_guidance_page.ui \
    mla_guidance_page.ui \
    newspaper.ui \
    magazine_page.ui
