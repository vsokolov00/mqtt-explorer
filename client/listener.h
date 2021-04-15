
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

