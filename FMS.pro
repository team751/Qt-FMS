#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T18:58:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FMS
TEMPLATE = app


SOURCES += src/main.cpp\
        src/statuswindow.cpp \
    widgets/coloredcirclewidget.cpp \
    widgets/coloredcircleindicator.cpp \
    src/matchtimingmanager.cpp \
    src/dspacketmaker.cpp \
    src/dssender.cpp \
    src/fms.cpp \
    src/dsreceiver.cpp \
    src/dspacketparser.cpp \
    src/teamstation.cpp

HEADERS  += src/statuswindow.h \
    widgets/coloredcirclewidget.h \
    widgets/coloredcircleindicator.h \
    src/matchtimingmanager.h \
    src/dspacketmaker.h \
    src/dssender.h \
    src/FMSDefs.h \
    src/fms.h \
    src/dsreceiver.h \
    src/dspacketparser.h \
    src/teamstation.h

FORMS    += forms/statuswindow.ui \
    widgets/coloredcirclewidget.ui \
    widgets/coloredcircleindicator.ui

INCLUDEPATH += widgets \
    /opt/local/include
