
#pragma once

#include <QObject>
#include "device_widget.h"

class DashboardController : public QObject
{
    Q_OBJECT

public:
    explicit DashboardController(QObject *parent = nullptr);
    ~DashboardController();

    void add_device(DeviceWidget* device = nullptr, QString topic = "");

private:
    std::vector<DeviceWidget*> _devices;
    std::map<std::string, DeviceWidget*> _topic_to_device;
};
