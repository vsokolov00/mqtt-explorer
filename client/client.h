
#pragma once

#include "listener.h"
#include "callback.h"
#include "json/json-forwards.h"
#include "json/json.h"

#include <string>
#include <thread>

class Client : public virtual mqtt::callback
{
    private:
        static ParsingLevel BINARY;
        static ParsingLevel STRING;
        static ParsingLevel JSON;
        static ParsingLevel JPG;
        static ParsingLevel PNG;
        static ParsingLevel GIF;
        static ParsingLevel ALL_IMAGES;

    public:
        static void add_parsing_level(ParsingLevel &current_levels, FileType file_type);
        static void remove_parsing_level(ParsingLevel &current_levels, FileType file_type);
    
    private:
        static void dummy_cb(void *object, const mqtt::token& token);

    private:
        void connected(const std::string &cause) override;
        void connection_lost(const std::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;

        mqtt::async_client _client;
        ParsingLevel _level;
        //Listeners _listeners;
        //Callbacks _callbacks;

        void *_connection_object;
        OnConnectionSuccessCB _connection_success_cb;
        OnConnectionLostCallback _connection_lost_cb;
        Listener _connect_listener;
        Listener _disconect_listener;

        void *_message_object;
        OnMessageArrivedCallback _message_arrived_cb;
        OnDeliveryCompleteCallback _delivery_complete_cb;
        Listener _publish_listener;

        Listener _subscribe_listener;
        Listener _unsubscribe_listener;

        Json::CharReader *_reader;
        std::mutex *_muttex;

    public:
        /*Client(const std::string server_address, const std::string &id, Listeners &listeners, 
               Callbacks &callbacks, ParsingLevel level);
        Client(const std::string server_address, const std::string &id, 
               Listeners &listeners, Callbacks &callbacks, FileType single_file_type);*/
        Client(const std::string server_address, const std::string &id, FileType single_file_type,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCallback connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCallback message_arrived_cb, 
               OnDeliveryCompleteCallback delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const std::string server_address, const std::string &id, ParsingLevel level,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCallback connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCallback message_arrived_cb, 
               OnDeliveryCompleteCallback delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const Client&) = delete;
        ~Client();

        bool connect(const mqtt::connect_options &connect_options);
        bool disconnect();
        void subscribe(const std::string topic, const int QOS);
        void unsubscribe(const std::string topic);
        void publish(const std::string topic, const std::string message);
};
