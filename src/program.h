
#pragma once

#include <QApplication>
#include <thread>

#include "mainwindow.h"
#include "client.h"
#include "connectioncontroller.h"
#include "messagecontroller.h"
#include "subscriptioncontroller.h"
#include "mqttreemodel.h"
#include "log.h"
#include "login.h"

class Program : public QObject
{
    Q_OBJECT

    private:
        Login *_login_window = nullptr;
        MainWindow *_main_window = nullptr;

        ConnectionController *_connection_controller = nullptr;
        MessageController *_message_controller = nullptr;
        SubscriptionController *_subscription_controller = nullptr;

        Client *_client = nullptr;
        std::mutex *_mutex;

    public:
        Program() = default;
        ~Program();
        Program(const Program&) = delete;

        void init();
        void start();
        void login_info_entered_cb();
};