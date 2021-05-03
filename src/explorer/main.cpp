//#include "login.h"
#include "main_view.h"

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
        Log::error("Memory allocation failed.");
        program.~Program();
        exit(99);
    }
    program.start();

    int return_value = application.exec();

    program.quit();

    return return_value;
}
