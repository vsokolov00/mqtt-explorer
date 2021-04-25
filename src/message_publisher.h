
#pragma once

#include "client.h"
#include <QVariant>

class MessagePublisher
{
    private:

        Client *_client;

    public:
        bool file_chosen = false;
        QVariant file_to_publish;
        FileType file_type;

        MessagePublisher(Client *client);
        ~MessagePublisher() = default;

        void publish_message(std::string topic, QVariant message);
};
