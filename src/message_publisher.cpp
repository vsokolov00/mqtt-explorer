
#include "message_publisher.h"

MessagePublisher::MessagePublisher(Client *client) : _client(client) {}

void MessagePublisher::publish_message(std::string topic, QVariant message)
{
    //publish&wait for feedback
    if (file_chosen)
    {
        //send chosen file
        _client->publish(topic, file_to_publish.toString().toStdString());
    }
    else
    {
        _client->publish(topic, message.toString().toStdString());
    }
}
