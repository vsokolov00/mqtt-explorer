#ifndef PUBLISHCONTROLLER_H
#define PUBLISHCONTROLLER_H

#include <QVariant>
#include <string>
#include <unistd.h>

class PublishController
{
public:
    PublishController();
    bool publish_msg(std::string topic, QVariant qv);
};

#endif // PUBLISHCONTROLLER_H
