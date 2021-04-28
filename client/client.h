
#pragma once

#include "json/json-forwards.h"
#include "json/json.h"

#include "listener.h"
#include <string>
#include <thread>


enum class FileType : unsigned short 
{
    BINARY = 0b1,
    STRING_UTF8 = 0b10,
    JSON = 0b100,
    JPG = 0b1000,
    PNG = 0b10000,
    GIF = 0b100000,
    ALL_IMAGES = 0b111100,
    ALL = 0b111111,
    AS_BINARY = 0b1000000,
    ALL_AS_BINARY = 0b1111111
};

using ParsingLevel = unsigned short;

struct String
{
    size_t size;
    const char *data;
};

struct Binary
{
    size_t size;
    const char *data;
};

union MessageData
{
    String string;
    Binary binary;
    Json::Value *json;
};

using OnConnectionSuccessCB = void(*)(void *, const std::string&);
using OnMessageArrivedCB = void(*)(void *, const std::string&, const MessageData&, FileType);
using OnConnectionLostCB = void(*)(void *, const std::string&);
using OnDeliveryCompleteCB = void(*)(void *, mqtt::delivery_token_ptr);

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
        static ParsingLevel AS_BINARY;

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

        void *_connection_object;
        OnConnectionSuccessCB _connection_success_cb;
        OnConnectionLostCB _connection_lost_cb;
        Listener _connect_listener;
        Listener _disconect_listener;

        void *_message_object;
        OnMessageArrivedCB _message_arrived_cb;
        OnDeliveryCompleteCB _delivery_complete_cb;
        Listener _publish_listener;

        Listener _subscribe_listener;
        Listener _unsubscribe_listener;

        Json::CharReader *_reader;
        std::mutex *_muttex;

    public:
        Client(const std::string server_address, const std::string &id, FileType single_file_type,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const std::string server_address, const std::string &id, ParsingLevel level,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const Client&) = delete;
        ~Client();

        bool connect(const mqtt::connect_options &connect_options);
        bool disconnect();
        void subscribe(const std::string topic, const int QOS);
        void unsubscribe(const std::string topic);
        int publish(const std::string topic, const std::string message);
};
