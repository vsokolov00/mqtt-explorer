
#pragma once

#include "login.h"
#include "mainwindow.h"
#include "client.h"

class Program
{
    private:
        Login *_login_window = nullptr;
        MainWindow *_main_window = nullptr;

        ConnectionController *_connection_controller = nullptr;
        MessageController *_message_controller = nullptr;
        SubscriptionController *_subscription_controller = nullptr;

        TreeModel *_tree_model = nullptr;
        Client *_client = nullptr;

    public:
        Program();
        ~Program();

        void init_program();
};