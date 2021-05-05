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
    _topic_to_device.insert({topic.toStdString() + device->get_name(), device});
}

void DashboardController::process_message(std::string topic, QByteArray payload)
{
    QPalette palette;

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
        } else if (type == DeviceType::LIGHT)
        {
            QString state(payload);
            if (state == "on" || state == "dimmed")
            {
                device->set_image(QImage(":/images/bulb_on.png"), 150, 150);
            } else if (state == "off")
            {
                device->set_image((QImage(":/images/bulb_off.png")), 150, 150);
            }
            if (state == "red")
            {
                palette.setColor(QPalette::Window, Qt::red);
                device->set_color(palette);
            } else if (state == "green")
            {
                palette.setColor(QPalette::Window, Qt::green);
                device->set_color(palette);
            } else if (state == "blue")
            {
                palette.setColor(QPalette::Window, Qt::blue);
                device->set_color(palette);
            } else if (state == "yellow")
            {
                palette.setColor(QPalette::Window, Qt::yellow);
                device->set_color(palette);
            } else if (state == "cyan")
            {
                palette.setColor(QPalette::Window, Qt::cyan);
                device->set_color(palette);
            } else if (state == "magneta")
            {
                palette.setColor(QPalette::Window, Qt::magenta);
                device->set_color(palette);
            } else if (state == "white")
            {
                palette.setColor(QPalette::Window, Qt::white);
                device->set_color(palette);
            }
            device->set_description(state);
        } else if (type == DeviceType::THERMOMETR)
        {
            device->set_description(QString(payload));
        } else {
            device->set_description(QString(payload));
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
