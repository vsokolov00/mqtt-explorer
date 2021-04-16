
#pragma once

#include <string>
#include "mqtt/async_client.h"

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
        
        Callbacks(void *object, OnConnectedCallback on_connected, OnMessageArrivedCallback on_message_arrived, 
                  OnConnectionLostCallback on_connection_lost, OnDeliveryCompleteCallback on_delivery_complete);
};
