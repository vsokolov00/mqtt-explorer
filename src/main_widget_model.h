
#pragma once

#include <QAbstractItemModel>

class MainWidgetModel
{
    public:
        MainWidgetModel();
        ~MainWidgetModel() = default;

//        void subscription_success(const std::string &topic);
//        void subscription_failure(const std::string &topic);

//        void unsubscription_success(const std::string &topic);
//        void unsubscription_failure(const std::string &topic);

        void delivery_complete(int message_id);
        void update_history();

        void connection_lost();
        void reconnect_failed(bool connection_exist, const std::string &server_address);
        void reconnect_failed();
};
