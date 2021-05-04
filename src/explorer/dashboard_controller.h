
#pragma once

#include <QObject>
#include "device_widget.h"

class DashboardController : public QObject
{
    Q_OBJECT

public:
    explicit DashboardController(QObject *parent = nullptr);
    void add_device(DeviceType type = DeviceType::ERR, QString name = "Device", QString topic = "");

private:
    std::vector<DeviceWidget*> devices;
    std::map<std::string, DeviceWidget*> topic_device;
};
