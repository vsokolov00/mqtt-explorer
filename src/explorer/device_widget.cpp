#include "device_widget.h"
#include "ui_device_widget.h"
#include "dashboard_controller.h"

DeviceWidget::DeviceWidget(QWidget *parent, DeviceType type, QString name, QString topic) :
    QWidget(parent),
    ui(new Ui::DeviceWidget),
    type(type),
    name(name),
    topic(topic)
{
    ui->setupUi(this);
    ui->name->setText(name);

    if (type == DeviceType::LIGHT)
    {
        set_image(QImage(":/images/bulb_off.png"), 150, 150);
    } else if (type == DeviceType::CAM)
    {
        set_image(QImage(":/images/cam.png"), 115, 115);
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

void DeviceWidget::set_image(QImage image, int width, int height)
{
    QPixmap pix_img = QPixmap::fromImage(image);
    ui->icon->setPixmap(pix_img.scaled(width, height, Qt::KeepAspectRatio));
    ui->icon->setVisible(true);
}

DeviceType DeviceWidget::get_type()
{
    return type;
}

std::string DeviceWidget::get_name()
{
    return name.toStdString();
}

std::string DeviceWidget::get_topic()
{
    return topic.toStdString();
}
