
##############################################################################################
# File:        explorer.pro                                 
# Case:        VUT, FIT, ICP, project                                      
# Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           
# Date:        summer semester 2021                                        
# Brief:       Qmake file used for a Makefile generation.
###############################################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

#CONFIG-=debug_and_release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += .
LIBS = -L../libs/client -lclient -L../libs/json -ljson -lpaho-mqttpp3 -lpaho-mqtt3a
QMAKE_CXXFLAGS += -std=c++17

DESTDIR         = ../bin/               # Target file directory
OBJECTS_DIR     = ../build/explorer     # Intermediate object files directory
MOC_DIR         = moc/                  # Generated moc_*.[cpp,h] files
UI_DIR          = ui/                   # Generated ui_*.h files 
RCC_DIR         = rrc/                  # Generated qrc_*.cpp files

SOURCES += \
    connection_controller.cpp \
    dashboard_controller.cpp \
    dashboard_view.cpp \
    delete_device_dialog.cpp \
    device_widget.cpp \
    flowlayout.cpp \
    login_view.cpp \
    main.cpp \
    main_view.cpp \
    message_controller.cpp \
    new_device_dialog.cpp \
    popup.cpp \
    subscription_controller.cpp \
    tree_item.cpp \
    tree_model.cpp \
    program.cpp \
    log.cpp

HEADERS += \
    connection_controller.h \
    dashboard_controller.h \
    dashboard_view.h \
    delete_device_dialog.h \
    device_widget.h \
    flowlayout.h \
    login_view.h \
    main_view.h \
    message_controller.h \
    new_device_dialog.h \
    popup.h \
    subscription_controller.h \
    tree_item.h \
    tree_model.h \
    program.h \
    log.h

FORMS += \
    resources/delete_device_dialog.ui \
    resources/new_device_dialog.ui \
    resources/device_widget.ui \
    resources/dashboard.ui \
    resources/login.ui \
    resources/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
