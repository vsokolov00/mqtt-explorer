
#pragma once

#include <QApplication>
#include <thread>

#include "log.h"

#include "client.h"
#include "main_widget_model.h"
#include "login_widget_model.h"
#include "tree_model.h"

#include "mainwindow.h"
#include "login.h"

#include "connectioncontroller.h"
#include "messagecontroller.h"
#include "subscriptioncontroller.h"


class Program : public QObject
{
    Q_OBJECT

    private:
        Client *_client = nullptr;
        TreeModel *_tree_model = nullptr;
        MainWidgetModel *_main_widget_model = nullptr;
        LoginWidgetModel *_login_widget_model = nullptr;

        Login *_login_view = nullptr;
        MainWindow *_main_view = nullptr;

        ConnectionController *_connection_controller = nullptr;
        MessageController *_message_controller = nullptr;
        SubscriptionController *_subscription_controller = nullptr;

        std::mutex *_mutex;

    public:
        Program() = default;
        ~Program();
        Program(const Program&) = delete;

        void init();
        void start();
        void login_info_entered_cb();
};