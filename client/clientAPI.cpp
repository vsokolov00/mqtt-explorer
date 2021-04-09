
#include "clientAPI.h"

ClientAPI::ClientAPI(ConnectListener &connect_listener, SubscribeListener &subscribe_listener, 
                     UnsubscribeListener &unsubscribe_listener, PublishListener &publish_listener,
                     DisconectListener &disconect_listener)
          :connect_listener(connect_listener), subscribe_listener(subscribe_listener), 
           unsubscribe_listener(unsubscribe_listener), publish_listener(publish_listener),
           disconect_listener(disconect_listener) {}

void ClientAPI::text_message(const std::string message, const std::string topic)
{
    std::cout << "Message on topic: " << topic << " arrived: " << message << std::endl;
}

void ClientAPI::connected()
{
    std::cout << "Connection succeded." << std::endl;
}

void ConnectListener::on_success(const mqtt::token& tok)
{
    (void) tok;
    // bug in paho library, function gets triggered twice
}

void ConnectListener::on_failure(const mqtt::token& tok)
{
    std::cout << "Connection to server: " << tok.get_connect_response().get_server_uri() << " failed." << std::endl;
}

void SubscribeListener::on_success(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Subscription to topic: '" << (*topics)[0] << "' succeded." << std::endl;
    }
}

void SubscribeListener::on_failure(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Subscription to topic: '" << (*topics)[0] << "' failed." << std::endl;
    }
}

void UnsubscribeListener::on_success(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Unsubscription to topic: '" << (*topics)[0] << "' succeded." << std::endl;
    }
}

void UnsubscribeListener::on_failure(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Unsubscription to topic: '" << (*topics)[0] << "' failed." << std::endl;
    }
}

void PublishListener::on_success(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Publish to topic: '" << (*topics)[0] << "' succeded." << std::endl;
    }
}

void PublishListener::on_failure(const mqtt::token& tok)
{
    mqtt::const_string_collection_ptr topics = tok.get_topics();
	if (topics != nullptr && !topics->empty())
    {
		std::cout << "Publish to topic: '" << (*topics)[0] << "' failed." << std::endl;
    }
}

void DisconectListener::on_success(const mqtt::token& tok)
{
    (void)tok;
    std::cout << "Disconect succeded." << std::endl;
    exit(0);
}

void DisconectListener::on_failure(const mqtt::token& tok)
{
    (void)tok;
    std::cout << "Disconect failed." << std::endl;
    exit(1);
}
