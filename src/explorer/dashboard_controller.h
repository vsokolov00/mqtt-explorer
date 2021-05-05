
#pragma once

#include <QObject>
#include "device_widget.h"
#include "log.h"

class DashboardController : public QObject
{
    Q_OBJECT

public:
    explicit DashboardController(QObject *parent = nullptr);
    ~DashboardController();

    void add_device(DeviceWidget* device = nullptr, QString topic = "");
    void process_message(std::string topic, QByteArray payload);

private:
    std::vector<DeviceWidget*> _devices;
    std::map<std::string, DeviceWidget*> _topic_to_device;
};
