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
LIBS = -fPIC

DESTDIR=bin/        #Target file directory
OBJECTS_DIR=build/  #Intermediate object files directory
MOC_DIR=view/       #Generated UI *.[cpp,h] files

SOURCES += \
    connectioncontroller.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    messagecontroller.cpp \
    mqttreemodel.cpp \
    subscriptioncontroller.cpp \
    treeitem.cpp

HEADERS += \
    connectioncontroller.h \
    mainwindow.h \
    messagecontroller.h \
    mqttreemodel.h \
    subscriptioncontroller.h \
    treeitem.h \
    login.h

FORMS += \
    view/ui/login.ui \
    view/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    view/ui/resources.qrc
