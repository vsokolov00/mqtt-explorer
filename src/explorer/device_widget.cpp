#include "device_widget.h"
#include "ui_device_widget.h"

DeviceWidget::DeviceWidget(QWidget *parent, DeviceType type, QString name, QString topic) :
    QWidget(parent),
    ui(new Ui::DeviceWidget)
{
    ui->setupUi(this);
    ui->name->setText(name);

    if (type == DeviceType::LIGHT)
    {
        QPixmap image = QPixmap::fromImage(QImage(":/images/bulb_off.png"));
        ui->icon->setPixmap(image.scaled(150,150, Qt::KeepAspectRatio));
        ui->icon->setVisible(true);
    } else if (type == DeviceType::CAM)
    {
        QPixmap image = QPixmap::fromImage(QImage(":/images/cam.png"));
        ui->icon->setPixmap(image.scaled(115,115, Qt::KeepAspectRatio));
        ui->icon->setVisible(true);
    } else if (type == DeviceType::HYGR)
    {

    } else if (type == DeviceType::MOVE)
    {

    } else if (type == DeviceType::RELAY)
    {

    } else if (type == DeviceType::THERMOMETR)
    {

    } else if (type == DeviceType::THERMOSTAT)
    {

    } else if (type == DeviceType::VALVE)
    {

    } else if (type == DeviceType::WATT)
    {

    }

}

DeviceWidget::~DeviceWidget()
{
    delete ui;
}
