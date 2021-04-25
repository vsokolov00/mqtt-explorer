
#pragma once

#include <string>
#include "client.h"
#include "mainwindow.h"
#include "log.h"

class SubscriptionController
{
    public:
        static void on_subscribe_success_cb(void *object, const mqtt::token &token);
        static void on_subscribe_failure_cb(void *object, const mqtt::token &token);

        static void on_unsubscribe_success_cb(void *object, const mqtt::token &token);
        static void on_unsubscribe_failure_cb(void *object, const mqtt::token &token);

    private:
        MainWindow *_main_window;

    public:
        SubscriptionController(MainWindow *main_window);

        void on_subscribe_success(const mqtt::token &token);
        void on_subscribe_failure(const mqtt::token &token);

        void on_unsubscribe_success(const mqtt::token &token);
        void on_unsubscribe_failure(const mqtt::token &token);
};
