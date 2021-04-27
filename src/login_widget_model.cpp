
#include "login_widget_model.h"

LoginWidgetModel::LoginWidgetModel() {}


void LoginWidgetModel::connection_failed(bool connection_exist, const std::string &server_address)
{   
    (void)connection_exist;
    (void)server_address;
    // TODO display red message to the user that login to server adddress failed - try again...
    // if the connection_exist is true, then inform also about this
}

void LoginWidgetModel::connection_failed()
{
    //TODO display red message
}
