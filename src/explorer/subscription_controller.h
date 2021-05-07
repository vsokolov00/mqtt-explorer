
/**
 * @file        subscription_controller.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     David Mihola, xmihol00@stud.fit.vutbr.cz; 
 *              Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
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

/**
 * @brief Manages subscription and unsubscription to to MQTT topics.
 **/
class SubscriptionController : public QObject
{
    Q_OBJECT

    public:
        /**
         * @brief Callback function called when subscription succeeds.
         * @param object user defined object, which will be casted to a SubscriptionController class object.
         * @param token token holding information about the successful subscription.
         **/
        static void on_subscribe_success_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when subscription failes.
         * @param object user defined object, which will be casted to a SubscriptionController class object.
         * @param token token holding information about the failed subscription.
         **/
        static void on_subscribe_failure_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when unsubscription succeeds.
         * @param object user defined object, which will be casted to a SubscriptionController class object.
         * @param token token holding information about the successful unsubscription.
         **/
        static void on_unsubscribe_success_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when unsubscription fails.
         * @param object user defined object, which will be casted to a SubscriptionController class object.
         * @param token token holding information about the failed unsubscription.
         **/
        static void on_unsubscribe_failure_cb(void *object, const mqtt::token &token);

    private:
        Client *_client = nullptr;

    public:
        SubscriptionController();
        ~SubscriptionController() = default;

        /**
         * @brief Registers a client used by the subscription controller.
         * @param client the client to be registered.
         **/
        void register_client(Client *client);

        /**
         * @brief Subscribes a given topic.
         * @param topic the subscribed topic.
         * @param QOS the quality of service of the subscribed topic.
         **/
        void subscribe(const std::string &topic, int QOS);

        /**
         * @brief Unsubscribes a given topic.
         * @param topic the unsubscribed topic.
         **/
        void unsubscribe(const std::string &topic);
        
        /**
         * @brief Called when subscription succeeds.
         * @param token token holding information about the successful subscription.
         **/
        void on_subscribe_success(const mqtt::token &token);

        /**
         * @brief Called when subscription fails.
         * @param token token holding information about the failed subscription.
         **/
        void on_subscribe_failure(const mqtt::token &token);

        /**
         * @brief Called when unsubscription succeeds.
         * @param token token holding information about the successful unsubscription.
         **/
        void on_unsubscribe_success(const mqtt::token &token);

        /**
         * @brief Called when unsubscription fails.
         * @param token token holding information about the failed unsubscription.
         **/
        void on_unsubscribe_failure(const mqtt::token &token);

    signals:
        /**
         * @brief Emits a signal registered by the main window @see MainView informing when subscription succeeds.
         * @param topic the subscribed topic.
         **/
        void subscription_success(const QString& topic);

        /**
         * @brief Emits a signal registered by the main window @see MainView informing when subscription fails.
         * @param topic the subscribed topic.
         **/
        void subscription_failure(const QString& topic);

        /**
         * @brief Emits a signal registered by the main window @see MainView informing when unsubscription succeeds.
         * @param topic the unsubscribed topic.
         **/
        void unsubscription_success(const QString& topic);

        /**
         * @brief Emits a signal registered by the main window @see MainView informing when unsubscription fails.
         * @param topic the unsubscribed topic.
         **/
        void unsubscription_failure(const QString& topic);

    public slots:
        /**
         * @brief Subscribes a new device added to the dasboard.
         * @param topic the topic of the newly added device.
         **/
        void new_dashboard_device(std::string topic);

        /**
         * @brief dashboard_device_deleted Unsubscribes a device deleted from the dasboard.
         * @param topic of deleted device.
         */
        void dashboard_device_deleted(std::string topic);
};
