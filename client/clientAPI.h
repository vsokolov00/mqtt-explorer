
#ifndef __CLIENTAPI_H__
#define __CLIENTAPI_H__

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>

#include "mqtt/async_client.h"

class ConnectListener : public virtual mqtt::iaction_listener
{
    void on_failure(const mqtt::token& tok) override;

    void on_success(const mqtt::token& tok) override;
};

class SubscribeListener : public virtual mqtt::iaction_listener
{
    void on_failure(const mqtt::token& tok) override;

    void on_success(const mqtt::token& tok) override;
};

class UnsubscribeListener : public virtual mqtt::iaction_listener
{
    void on_failure(const mqtt::token& tok);

    void on_success(const mqtt::token& tok);
};

class PublishListener : public virtual mqtt::iaction_listener
{
    void on_failure(const mqtt::token& tok);

    void on_success(const mqtt::token& tok);
};

class ClientAPI
{
    public:
        ClientAPI();

        ClientAPI(ConnectListener &connect_listener, SubscribeListener &subscribe_listener, 
                  UnsubscribeListener &unsubscribe_listener, PublishListener &publish_listener);

        ConnectListener connect_listener;

        SubscribeListener subscribe_listener;

        UnsubscribeListener unsubscribe_listener;

        PublishListener publish_listener;

        void text_message(const std::string message, const std::string topic);

        void connected();
};

#endif // __CLIENTAPI_H__
