
#pragma once

#include <string>
#include <locale> 

#include "mqtt/async_client.h"
#include "json/json-forwards.h"
#include "json/json.h"

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


using ParsingLevel = unsigned short;

enum class FileType : unsigned short 
{
    ALL = 0xFFFF,
    BINARY = 0b1,
    STRING_UTF8 = 0b10,
    JSON = 0b100,
    JPG = 0b1000,
    PNG = 0b10000,
    GIF = 0b100000,
    ALL_IMAGES = 0b111100
};

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

class Callbacks
{
    public:
        void *on_connected_object;
        OnConnectionSuccessCB on_connected;

        void *on_message_arrived_object;
        OnMessageArrivedCB on_message_arrived;

        void *on_connection_lost_object;
        OnConnectionLostCB on_connection_lost;

        void *on_delivery_complete_object;
        OnDeliveryCompleteCB on_delivery_complete;
    
        Callbacks(void *on_connected_object, OnConnectionSuccessCB on_connected, 
                  void *on_message_arrived_object, OnMessageArrivedCB on_message_arrived, 
                  void *on_connection_lost_object, OnConnectionLostCB on_connection_lost, 
                  void *on_delivery_complete_object, OnDeliveryCompleteCB on_delivery_complete);
        
        Callbacks(void *object, OnConnectionSuccessCB on_connected, OnMessageArrivedCB on_message_arrived, 
                  OnConnectionLostCB on_connection_lost, OnDeliveryCompleteCB on_delivery_complete);
};

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
        void connected(const std::string &cause) override;
        void connection_lost(const std::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;

        mqtt::async_client _client;
        Listeners _listeners;
        Callbacks _callbacks;

        ParsingLevel _level;
        Json::CharReader *_reader;
        std::mutex *_muttex;

    public:
        Client(const std::string server_address, const std::string &id, Listeners &listeners, 
               Callbacks &callbacks, ParsingLevel level);
        Client(const std::string server_address, const std::string &id, 
               Listeners &listeners, Callbacks &callbacks, FileType single_file_type);
        Client(const Client&) = delete;
        ~Client();

        bool connect(const mqtt::connect_options &connect_options);
        bool disconnect();
        void subscribe(const std::string topic, const int QOS);
        void unsubscribe(const std::string topic);
        void publish(const std::string topic, const std::string message);
};
