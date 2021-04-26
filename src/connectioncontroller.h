
#pragma once

#include <string>
#include <thread>

#include "client.h"
#include "mainwindow.h"
#include "login_widget_model.h"

class ConnectionController
{
    public:
        static void on_connection_success_cb(void *object, const std::string &cause);
        static void on_connection_failure_cb(void *object, const mqtt::token &token);

        static void on_disconnection_success_cb(void *object, const mqtt::token &token);
        static void on_disconnection_failure_cb(void *object, const mqtt::token &token);

        static void on_connection_lost_cb(void *object, const std::string &cause);

    private:
        std::mutex *_mutex;

        bool _connection_success = false;
        bool _connection_exist = true;
        std::string _server_address;

    public:
        ConnectionController(std::mutex *mutex);
        ~ConnectionController() = default;

        void on_connection_success(const std::string &cause);
        void on_connection_failure(const mqtt::token &token);

        void on_disconnection_success(const mqtt::token &token);
        void on_disconnection_failure(const mqtt::token &token);

        void on_connection_lost(const std::string &cause);

        void connect(const std::string &server_address, const std::string &user_name, const std::string &password,
                     bool clean_session);

        bool get_connection_status();
        bool get_connection_existance();
        std::string get_server_address() const;
};
