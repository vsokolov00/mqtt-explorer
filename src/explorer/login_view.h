
#pragma once

#include <QMovie>
#include <QMainWindow>
#include <string>

//TODO remove
#include <thread>
#include <chrono>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"
#include "connection_controller.h"
#include "popup.h"

namespace Ui { class Login; }

class Program;


class LoginView: public QMainWindow
{
    Q_OBJECT

    private slots:
        void on_connect_clicked();

    private:
        Ui::Login *_ui = nullptr;

        PopUp* pop_up;

        ConnectionController *_connection_controller = nullptr;

        void show_popup();

    public:
        LoginView(ConnectionController *connection_cotroller);
        ~LoginView();
    public slots:
        void connection_failure_popup_set();

};
