
#pragma once

#include <QWidget>

enum class DeviceType : unsigned short
{
    ERR = 0b0,
    LIGHT = 0b1,
    THERMOMETR = 0b10,
    HYGR = 0b100,
    WATT = 0b1000,
    MOVE = 0b10000,
    CAM = 0b100000,
    RELAY = 0b111100,
    VALVE = 0b111111,
    THERMOSTAT = 0b1000000
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
