
#include "listener.h"

Listener::Listener(void *class_object, OnSuccessCallback on_success_callback, 
                           OnFailureCallback on_failure_callback)
             : _class_object(class_object), _on_success_callback(on_success_callback),
               _on_failure_callback(on_failure_callback) {}

void Listener::on_success(const mqtt::token& tok)
{
    _on_success_callback(_class_object, tok);
}

void Listener::on_failure(const mqtt::token& tok)
{
    _on_failure_callback(_class_object, tok);
}

Listeners::Listeners(Listener &connect_listener, Listener &subscribe_listener, Listener &unsubscribe_listener, 
                     Listener &publish_listener, Listener &disconect_listener)
          : connect_listener(connect_listener), subscribe_listener(subscribe_listener), unsubscribe_listener(unsubscribe_listener),
            publish_listener(publish_listener), disconect_listener(disconect_listener) {}

