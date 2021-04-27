
#include "main_widget_model.h"

MainWidgetModel::MainWidgetModel(){}




//void MainWidgetModel::delivery_complete(int message_id)
//{
//    (void)message_id;
//    //TODO find the ID and mark the message as delivered
//}


//void MainWidgetModel::subscription_success(const std::string &topic)
//{
//    (void)topic;
//    // TODO display a message (green for X seconds) with the subscribed topic
//}

//void MainWidgetModel::subscription_failure(const std::string &topic)
//{
//    (void)topic;
//    // TODO display a message (red for X seconds) with the subscribed topic
//}

//void MainWidgetModel::unsubscription_success(const std::string &topic)
//{
//    (void)topic;
//    // TODO display a message (green for X seconds) with the unsubscribed topic
//}

//void MainWidgetModel::unsubscription_failure(const std::string &topic)
//{
//    (void)topic;
//    // TODO display a message (red for X seconds) with the unsubscribed topic
//}

void MainWidgetModel::connection_lost()
{
    //TODO display a window conenction lost with reconnect button and got to login page
}

void MainWidgetModel::reconnect_failed(bool connection_exist, const std::string &server_address)
{
    (void)connection_exist;
    (void)server_address;
    //TODO display a window reconnect failed with reconnect button and got to login page
}

void MainWidgetModel::reconnect_failed()
{
    //TODO display a window reconnect failed with reconnect button and got to login page
}
