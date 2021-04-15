
#include "client.h"

Client::Client(mqtt::connect_options &options, const std::string server_address, Listeners &listeners, Callbacks &callbacks)
       : _options(options), _client(server_address, "random_id_ujyt"), _listeners(listeners), _callbacks(callbacks)
{
    _client.set_callback(*this);
}

void Client::connected(const std::string &cause)
{   
    (void)cause;
}

void Client::connection_lost(const std::string &cause)
{
    _callbacks.on_connection_lost(_callbacks.on_connection_lost_object, cause);
}

void Client::message_arrived(mqtt::const_message_ptr msg)
{
    _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, msg);
}

void Client::delivery_complete(mqtt::delivery_token_ptr token)
{
    _callbacks.on_delivery_complete(_callbacks.on_delivery_complete_object, token);
}

void Client::connect()
{
    _client.connect(_options, nullptr, _listeners.connect_listener);
}

void Client::disconnect()
{
    _client.disconnect(nullptr, _listeners.disconect_listener)->wait();
}

void Client::subscribe(const std::string topic, const int QOS)
{
    _client.subscribe(topic, QOS, nullptr, _listeners.subscribe_listener);
}

void Client::unsubscribe(const std::string topic)
{
    _client.unsubscribe(topic, nullptr, _listeners.unsubscribe_listener);
}

void Client::publish(const std::string topic, const std::string message)
{
    _client.publish(mqtt::make_message(topic, message), nullptr, _listeners.publish_listener);
}
