
/**
 * @file        subscription_controller.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages subscription and unsubscription to MQTT topics. 
 **/

#pragma once

#include <string>
#include <QObject>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"


class SubscriptionController : public QObject
{
    Q_OBJECT
    public:
        static void on_subscribe_success_cb(void *object, const mqtt::token &token);
        static void on_subscribe_failure_cb(void *object, const mqtt::token &token);

        static void on_unsubscribe_success_cb(void *object, const mqtt::token &token);
        static void on_unsubscribe_failure_cb(void *object, const mqtt::token &token);

    private:
        Client *_client = nullptr;

    public:
        SubscriptionController();
        ~SubscriptionController() = default;

        void register_client(Client *client);

        void subscribe(const std::string &topic, int QOS);
        void unsubscribe(const std::string &topic);

        void on_subscribe_success(const mqtt::token &token);
        void on_subscribe_failure(const mqtt::token &token);

        void on_unsubscribe_success(const mqtt::token &token);
        void on_unsubscribe_failure(const mqtt::token &token);
    signals:
        void subscription_success(const QString& topic);
        void subscription_failure(const QString& topic);
        void unsubscription_success(const QString& topic);
        void unsubscription_failure(const QString& topic);
};
