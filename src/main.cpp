//#include "login.h"
#include "mainwindow.h"

#include "program.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    Program program;
    try
    {
        program.init();
    }
    catch (std::bad_alloc &e)
    {
        (void)e;
        program.~Program();
        exit(99);
    }
    program.start();

    return application.exec();
}
