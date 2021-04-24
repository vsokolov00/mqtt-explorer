#include "publishcontroller.h"

PublishController::PublishController()
{

}

bool PublishController::publish_msg(std::string topic, QVariant qv)
{
    //publish&wait for feedback
    sleep(1);
    return true;
}
