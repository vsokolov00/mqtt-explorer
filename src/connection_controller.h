
#pragma once

#include <string>
#include <thread>

#include "client.h"
#include "login_widget_model.h"
#include "log.h"

using CBObject = void *;
using ConnectCB = void(*)(void *, const std::string&, const std::string&, const mqtt::connect_options&);
using DisconnectCB = void(*)(void *);

class ConnectionController : public QObject
{
    Q_OBJECT

    public:
        static void on_connection_success_cb(void *object, const std::string &cause);
        static void on_connection_failure_cb(void *object, const mqtt::token &token);

        static void on_disconnection_success_cb(void *object, const mqtt::token &token);
        static void on_disconnection_failure_cb(void *object, const mqtt::token &token);

        static void on_connection_lost_cb(void *object, const std::string &cause);

    private:
        std::mutex *_mutex;
        Client *_client;

        CBObject _connection_object = nullptr;
        ConnectCB _connection_cb = nullptr;
        DisconnectCB _disconnect_cb = nullptr;

        LoginWidgetModel *_login_widget_model;

        mqtt::connect_options _connection_options;
        bool _reconnect = false;
        bool _connection_status = false;

    public:
        ConnectionController(std::mutex *mutex, CBObject connection_object, ConnectCB connection_cb, DisconnectCB disconnect_cb, LoginWidgetModel *login_widget_model);
        ~ConnectionController() = default;

        void register_client(Client *client);
        bool get_connection_status();

        void on_connection_success(const std::string &cause);
        void on_connection_failure(const mqtt::token &token);

        void on_disconnection_success(const mqtt::token &token);
        void on_disconnection_failure(const mqtt::token &token);

        void on_connection_lost(const std::string &cause);

        void connect(const std::string &server_address, const std::string &id, const std::string &user_name, 
                     const std::string &password, bool clean_session);
        void disconnect();
        void reconnect();
        void go_to_login_view();

    signals:
        void connection_lost();
        void reconnect_failed(bool connection_exist, const std::string &server_address);
        void reconnect_failed();
        void connection_failed(QString, bool);
};
