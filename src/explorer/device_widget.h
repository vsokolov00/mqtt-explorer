
#pragma once

#include <QWidget>

enum class DeviceType : unsigned
{
    ERR = 0,
    LIGHT = 1,
    THERMOMETR = 2,
    HYGR = 3,
    WATT = 4,
    MOVE = 5,
    CAM = 6,
    RELAY = 7,
    VALVE = 8,
    THERMOSTAT = 9,
    LOCK = 10
};

namespace Ui {
class DeviceWidget;
}

class DeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceWidget(QWidget *parent = nullptr, DeviceType type = DeviceType::ERR, QString name = "Device", QString topic = "");
    ~DeviceWidget();

private:
    Ui::DeviceWidget *ui;
};
