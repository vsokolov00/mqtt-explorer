
/**
 * @file        device_widget.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the DasboardWidget class.
 **/

#include "device_widget.h"
#include "ui_device_widget.h"
#include "dashboard_controller.h"

DeviceWidget::DeviceWidget(QWidget *parent, DeviceType type, QString name, QString topic) :
    QWidget(parent),
    _ui(new Ui::DeviceWidget),
    _type(type),
    _name(name),
    _topic(topic)
{
    _ui->setupUi(this);
    _ui->name->setText(_name);

    if (_type == DeviceType::LIGHT)
    {
        set_image(QImage(":/images/bulb_off.png"), 100, 100);
    } else if (_type == DeviceType::CAM)
    {
        set_image(QImage(":/images/cam.png"), 100, 100);
    } else if (_type == DeviceType::HYGR)
    {

    } else if (_type == DeviceType::MOVE)
    {

    } else if (_type == DeviceType::RELAY)
    {

    } else if (_type == DeviceType::THERMOMETR)
    {

    } else if (_type == DeviceType::THERMOSTAT)
    {

    } else if (_type == DeviceType::VALVE)
    {

    } else if (_type == DeviceType::WATT)
    {

    }
}

DeviceWidget::~DeviceWidget()
{
    delete _ui;
}

void DeviceWidget::set_image(QImage image, int width, int height)
{
    _ui->icon->clear();
    QPixmap pix_img = QPixmap::fromImage(image);
    _ui->icon->setPixmap(pix_img.scaled(width, height, Qt::KeepAspectRatio));
    _ui->icon->setVisible(true);
}

void DeviceWidget::set_color(QPalette color)
{
    _ui->icon->clear();
    _ui->icon->setAutoFillBackground(true);
    _ui->icon->setPalette(color);
    _ui->icon->setMinimumSize(100, 100);
    _ui->icon->setMaximumSize(100, 100);
}

void DeviceWidget::set_description(QString text)
{
    _ui->description->setText(text);
}

void DeviceWidget::set_chart()
{
    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPixmap p = chartView->grab();

    QLabel* img = new QLabel(this);
    img->setWindowFlags(Qt::Window);
    img->setPixmap(p);
    img->setAttribute(Qt::WA_DeleteOnClose);
    img->show();
}

DeviceType DeviceWidget::get_type()
{
    return _type;
}

std::string DeviceWidget::get_name()
{
    return _name.toStdString();
}

std::string DeviceWidget::get_topic()
{
    return _topic.toStdString();
}
