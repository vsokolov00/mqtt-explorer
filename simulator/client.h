
#pragma once

#include <string>
#include "mqtt/async_client.h"

using OnSuccessCallback = void(*)(void *, const mqtt::token&);
using OnFailureCallback = void(*)(void *, const mqtt::token&);

class Listener : public virtual mqtt::iaction_listener
{
    private:
        void *_class_object;
        OnSuccessCallback _on_success_callback;
        OnFailureCallback _on_failure_callback;

        void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override;

    public:
        Listener(void *class_object, OnSuccessCallback on_success_callback, OnFailureCallback on_failure_callback);
};

class Listeners
{
    public:
        Listener connect_listener;
        Listener subscribe_listener;
        Listener unsubscribe_listener;
        Listener publish_listener;
        Listener disconect_listener;

        Listeners(Listener &connect_listener, Listener &subscribe_listener, Listener &unsubscribe_listener, 
                  Listener &publish_listener, Listener &disconect_listener);
};


using OnConnectedCallback = void(*)(void *, const std::string&);
using OnMessageArrivedCallback = void(*)(void *, mqtt::const_message_ptr);
using OnConnectionLostCallback = void(*)(void *, const std::string&);
using OnDeliveryCompleteCallback = void(*)(void *, mqtt::delivery_token_ptr);

class Callbacks
{
    public:
        void *on_connected_object;
        OnConnectedCallback on_connected;

        void *on_message_arrived_object;
        OnMessageArrivedCallback on_message_arrived;

        void *on_connection_lost_object;
        OnConnectionLostCallback on_connection_lost;

        void *on_delivery_complete_object;
        OnDeliveryCompleteCallback on_delivery_complete;
    
        Callbacks(void *on_connected_object, OnConnectedCallback on_connected, 
                  void *on_message_arrived_object, OnMessageArrivedCallback on_message_arrived, 
                  void *on_connection_lost_object, OnConnectionLostCallback on_connection_lost, 
                  void *on_delivery_complete_object, OnDeliveryCompleteCallback on_delivery_complete);
};

class Client : public virtual mqtt::callback
{
    private:
        void connected(const std::string &cause) override;
        void connection_lost(const std::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;

        mqtt::connect_options& _options;
        mqtt::async_client _client;

        Listeners _listeners;
        Callbacks _callbacks;

    public:
        Client(mqtt::connect_options &options, const std::string server_address, Listeners &listeners, Callbacks &callbacks);

        void connect();
        void disconnect();
        void subscribe(const std::string topic, const int QOS);
        void unsubscribe(const std::string topic);
        void publish(const std::string topic, const std::string message);
};
