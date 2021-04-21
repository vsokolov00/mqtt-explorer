
#pragma once

#include <string>

#include "mqtt/async_client.h"
#include "json/json-forwards.h"
#include "json/json.h"



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

using OnConnectedCallback = void(*)(void *, const std::string&);
using OnMessageArrivedCallback = void(*)(void *, const std::string&, const MessageData&, FileType);
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
        
        Callbacks(void *object, OnConnectedCallback on_connected, OnMessageArrivedCallback on_message_arrived, 
                  OnConnectionLostCallback on_connection_lost, OnDeliveryCompleteCallback on_delivery_complete);
};
