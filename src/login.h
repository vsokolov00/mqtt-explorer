
#pragma once

#include <QMainWindow>
#include <string>

//TODO remove
#include <thread>
#include <chrono>

#include "client.h"
#include "log.h"
#include "login_widget_model.h"
#include "connectioncontroller.h"

namespace Ui { class Login; }

class Program;

//TODO rename to MainView and the file to main_view.h
class Login: public QMainWindow
{
    Q_OBJECT

    private slots:
        void on_connect_clicked();

    private:
        Ui::Login *_ui = nullptr;

        LoginWidgetModel *_login_widget_model = nullptr;

        ConnectionController *_connection_controller = nullptr;

    public:
        Login(LoginWidgetModel *login_widget_model, ConnectionController *connection_cotroller);
        ~Login();
};
