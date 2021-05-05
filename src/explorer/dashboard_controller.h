
#pragma once

#include <QObject>
#include "device_widget.h"
#include "log.h"

class DashboardView;

class DashboardController : public QObject
{
    Q_OBJECT

private:
    DashboardView *_dashboard_window = nullptr;

public:
    std::map<std::string, DeviceWidget*> topic_to_device;

    explicit DashboardController(QObject *parent = nullptr);
    ~DashboardController();

    void register_dashboard_view(DashboardView *dashboard_window);
    void add_device(DeviceWidget* device);
    void process_message(std::string topic, QByteArray payload);
    void show_dashboard();
};
