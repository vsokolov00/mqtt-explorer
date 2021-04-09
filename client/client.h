
#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "clientAPI.h"

class Client : public virtual mqtt::callback
{
    private:
        mqtt::connect_options& _options;

        ClientAPI _API;

        mqtt::async_client _client;

        void connected(const std::string& cause) override;

        void connection_lost(const std::string& cause) override;

        void message_arrived(mqtt::const_message_ptr msg) override;

        void delivery_complete(mqtt::delivery_token_ptr token) override;

    public:
        Client(mqtt::connect_options &options, ClientAPI &API, const std::string server_address);

        void connect();

        void disconnect();

        void subscribe(const std::string topic, const int QOS);

        void unsubscribe(const std::string topic);

        void publish(const std::string topic, const std::string message);
};

#endif //__CLIENT_H__
