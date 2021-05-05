#include "dashboard_controller.h"
#include "dashboard_view.h"

DashboardController::DashboardController(QObject *parent)
                    : QObject(parent) {}

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

void DashboardController::process_message(std::string topic, QByteArray payload)
{

    if (_topic_to_device.find(topic) == _topic_to_device.end())
    {
        return;
    }
    else
    {
        auto device = _topic_to_device.at(topic);
        auto type = device->get_type();

        if (type == DeviceType::CAM)
        {
            QImage i;
            i.loadFromData(payload);
            device->set_image(i, 115, 115);
        }
        Log::log(topic);
    }
}

void DashboardController::register_dashboard_view(DashboardView *dashboard_window)
{
    _dashboard_window = dashboard_window;
}

void DashboardController::show_dashboard()
{
    _dashboard_window->show();
}
