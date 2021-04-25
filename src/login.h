
#pragma once

#include <QMainWindow>
#include <string>

#include "client.h"
#include "log.h"

namespace Ui { class Login; }

class Program;

class Login: public QMainWindow //TODO rename class and file to login_window
{
    Q_OBJECT

    private slots:
        void on_connect_clicked();

    signals:
        void login_info_entered();

    private:
        Ui::Login *_ui = nullptr;

        mqtt::connect_options _connection_options;
        std::string _server_address;
        std::string _id;

    public:
        Login();
        ~Login();

        void get_login_info(Program *program);
        void connection_failed(bool connection_exist, const std::string &server_address);
        void connection_failed();

        mqtt::connect_options get_connection_options() const;
        std::string get_server_address() const;
        std::string get_id() const;
};
