
#pragma once

#include <QAbstractItemModel>

class LoginWidgetModel
{
    public:
        LoginWidgetModel();
        ~LoginWidgetModel() = default;

        void connection_failed(bool connection_exist, const std::string &server_address);
//        void connection_failed();
};
