#include "dashboard_controller.h"

DashboardController::DashboardController(QObject *parent) : QObject(parent){}

DashboardController::~DashboardController()
{
    for (auto ptr : _devices)
    {
        delete ptr;
    }
}

void DashboardController::add_device(DeviceWidget* device, QString topic)
{
    _devices.push_back(device);
    _topic_to_device.insert({topic.toStdString(), device});
}
