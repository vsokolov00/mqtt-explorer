
#pragma once

#include <QMainWindow>
#include <string>

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

    signals:
        void login_info_entered();

    private:
        Ui::Login *_ui = nullptr;

        LoginWidgetModel *_login_widget_model = nullptr;

        ConnectionController *_connection_controller = nullptr;

        mqtt::connect_options _connection_options;
        std::string _server_address;
        std::string _id;

    public:
        Login(LoginWidgetModel *login_widget_model, ConnectionController *connection_cotroller);
        ~Login();

        void get_login_info(Program *program);
        void connection_failed(bool connection_exist, const std::string &server_address);
        void connection_failed();

        mqtt::connect_options get_connection_options() const;
        std::string get_server_address() const;
        std::string get_id() const;
};
