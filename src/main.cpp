#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Login w;
    // window.show_login()
    w.show();
    return a.exec();
}
