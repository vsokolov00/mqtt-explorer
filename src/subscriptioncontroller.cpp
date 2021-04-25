#include "subscriptioncontroller.h"

SubscriptionController::SubscriptionController(MainWindow *main_window) : _main_window(main_window) {}

void SubscriptionController::on_subscribe_success_cb(void *object, const mqtt::token &token)
{
    SubscriptionController *subscription_controller = static_cast<SubscriptionController *>(object);
    subscription_controller->on_subscribe_success(token);
}

void SubscriptionController::on_subscribe_failure_cb(void *object, const mqtt::token &token)
{
    SubscriptionController *subscription_controller = static_cast<SubscriptionController *>(object);
    subscription_controller->on_subscribe_failure(token);
}

void SubscriptionController::on_unsubscribe_success_cb(void *object, const mqtt::token &token)
{
    SubscriptionController *subscription_controller = static_cast<SubscriptionController *>(object);
    subscription_controller->on_unsubscribe_success(token);
}
void SubscriptionController::on_unsubscribe_failure_cb(void *object, const mqtt::token &token)
{
    SubscriptionController *subscription_controller = static_cast<SubscriptionController *>(object);
    subscription_controller->on_unsubscribe_failure(token);
}

void SubscriptionController::on_subscribe_success(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::log("Successful subscription to topic: " + (*topics)[i]);
        _main_window->subscription_success((*topics)[i]);
    }
}

void SubscriptionController::on_subscribe_failure(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::log("Unsuccessful subscription to topic: " + (*topics)[i]);
        _main_window->subscription_failure((*topics)[i]);
    }
}

void SubscriptionController::on_unsubscribe_success(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::log("Successful unsubscription of topic: " + (*topics)[i]);
        _main_window->unsubscription_success((*topics)[i]);
    }
}

void SubscriptionController::on_unsubscribe_failure(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::log("Unsuccessful unsubscription of topic: " + (*topics)[i]);
        _main_window->unsubscription_failure((*topics)[i]);
    }
}
