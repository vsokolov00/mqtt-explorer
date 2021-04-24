#ifndef SUBSCRIPTIONCONTROLLER_H
#define SUBSCRIPTIONCONTROLLER_H

#include<string>

class SubscriptionController
{
public:
    SubscriptionController();
    bool subscribe(std::string topic);
};

#endif // SUBSCRIPTIONCONTROLLER_H
