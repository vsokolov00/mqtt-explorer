QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#CONFIG-=debug_and_release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH = ./mqtt_paho/libs/
INCLUDEPATH += ./mqtt_paho/headers/
INCLUDEPATH += .
LIBS = -fPIC -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3as -lpaho-mqtt3c -lpaho-mqtt3cs

DESTDIR=bin/ #Target file directory
OBJECTS_DIR=build/ #Intermediate object files directory
MOC_DIR=build/

SOURCES += \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp

HEADERS += \
    mainmenu.h \
    mainwindow.h

FORMS += \
    ui/mainmenu.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
