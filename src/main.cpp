//#include "login.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.create_controllers();
    w.login();

    return a.exec();
}
