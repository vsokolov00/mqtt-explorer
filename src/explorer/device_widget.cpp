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
    ui->icon->clear();
    QPixmap pix_img = QPixmap::fromImage(image);
    ui->icon->setPixmap(pix_img.scaled(width, height, Qt::KeepAspectRatio));
    ui->icon->setVisible(true);
}

void DeviceWidget::set_color(QPalette color)
{
    ui->icon->clear();
    ui->icon->setAutoFillBackground(true);
    ui->icon->setPalette(color);
    ui->icon->setGeometry(0,0,150,150);
}

void DeviceWidget::set_description(QString text)
{
    ui->description->setText(text);
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
    img->show();
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
