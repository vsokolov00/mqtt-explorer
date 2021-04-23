
#pragma once

#include "mqtt/async_client.h"
#include "client.h"

class ClientAPI
{
    private:
        Listener _connect_listener;
        Listener _subscribe_listener;
        Listener _unsubscribe_listener;
        Listener _publish_listener;
        Listener _disconnect_listener;
        Listeners _listeners;
        Callbacks _callbacks;
        Client _client;
    
    public:
        ClientAPI(void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
                  OnConnectionLostCallback connection_lost_cb, 
                  void *message_object, OnMessageArrivedCallback message_arrived_cb, OnDeliveryCompleteCallback delivery_completed_cb,
                  void *publish_object, OnPublishSucessCB publish_success_cb, OnSubscribeFailureCB publish_failure_cb,
                  void *subscribe_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
                  void *unsubscribe_object, OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb,
                  void *disconnect_object, OnDisconectSucessCB disconnect_success, OnDisconectFailureCB disconnect_failure_cb
                  );
};
