QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG-=debug_and_release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += .
LIBS = -L../libs/client -lclient -L../libs/json -ljson -lpaho-mqttpp3 -lpaho-mqtt3a
QMAKE_CXXFLAGS += -Wno-unused-result -Wno-unused-parameter -std=c++17

DESTDIR= ../bin/        #Target file directory
OBJECTS_DIR= ../build/explorer  #Intermediate object files directory
MOC_DIR= view/       #Generated UI *.[cpp,h] files

SOURCES += \
    connection_controller.cpp \
    dashboard_controller.cpp \
    dashboard_view.cpp \
    device_widget.cpp \
    flowlayout.cpp \
    login_view.cpp \
    main.cpp \
    main_view.cpp \
    message_controller.cpp \
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
    device_widget.h \
    flowlayout.h \
    login_view.h \
    main_view.h \
    message_controller.h \
    popup.h \
    subscription_controller.h \
    tree_item.h \
    tree_model.h \
    program.h \
    log.h

FORMS += \
    view/ui/device_widget.ui \
    view/ui/dashboard.ui \
    view/ui/login.ui \
    view/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    view/ui/resources.qrc
