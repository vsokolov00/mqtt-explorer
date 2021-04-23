
#include "callback.h"

Callbacks::Callbacks(void *on_connected_object, OnConnectionSuccessCB on_connected, 
                     void *on_message_arrived_object, OnMessageArrivedCallback on_message_arrived, 
                     void *on_connection_lost_object, OnConnectionLostCallback on_connection_lost, 
                     void *on_delivery_complete_object, OnDeliveryCompleteCallback on_delivery_complete)
          : on_connected_object(on_connected_object), on_connected(on_connected), 
            on_message_arrived_object(on_message_arrived_object), on_message_arrived(on_message_arrived), 
            on_connection_lost_object(on_connection_lost_object), on_connection_lost(on_connection_lost),
            on_delivery_complete_object(on_delivery_complete_object), on_delivery_complete(on_delivery_complete) {}

Callbacks::Callbacks(void *object, OnConnectionSuccessCB on_connected, OnMessageArrivedCallback on_message_arrived, 
                  OnConnectionLostCallback on_connection_lost, OnDeliveryCompleteCallback on_delivery_complete)
          : on_connected_object(object), on_connected(on_connected), 
            on_message_arrived_object(object), on_message_arrived(on_message_arrived), 
            on_connection_lost_object(object), on_connection_lost(on_connection_lost),
            on_delivery_complete_object(object), on_delivery_complete(on_delivery_complete) {}
