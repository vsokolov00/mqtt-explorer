//#include "login.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.init_controllers();
    w.init_models();
    w.login();

    return a.exec();
}
