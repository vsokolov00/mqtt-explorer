
#pragma once

#include "listener.h"
#include "callback.h"

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
