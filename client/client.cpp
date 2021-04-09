
#include "client.h"

Client::Client(mqtt::connect_options &options, ClientAPI &API, const std::string server_address)
       :_options(options), _API(API), _client(server_address, "random_id_ujyt")
{
    _client.set_callback(*this);
}

void Client::connected(const std::string& cause)
{   
    (void)cause;
    _API.connected();
}

void Client::connection_lost(const std::string& cause)
{
    std::cout << "Connection lost " << cause << std::endl;
}

void Client::message_arrived(mqtt::const_message_ptr msg)
{
    _API.text_message(msg->to_string(), msg->get_topic());
}

void Client::delivery_complete(mqtt::delivery_token_ptr token)
{
    std::cout << "Delivery of message: " << token.get()->get_message().get()->to_string() << " is completed." << std::endl;
}

void Client::connect()
{
    _client.connect(_options, nullptr, _API.connect_listener);
}

void Client::disconnect()
{
    _client.disconnect(nullptr, _API.disconect_listener)->wait();
}

void Client::subscribe(const std::string topic, const int QOS)
{
    _client.subscribe(topic, QOS, nullptr, _API.subscribe_listener);
}

void Client::unsubscribe(const std::string topic)
{
    _client.unsubscribe(topic, nullptr, _API.unsubscribe_listener);
}

void Client::publish(const std::string topic, const std::string message)
{
    _client.publish(mqtt::make_message(topic, message), nullptr, _API.publish_listener);
}
