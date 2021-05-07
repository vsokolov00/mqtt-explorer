
/**
 * @file        device_widget.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 *              David Mihola, xmihol00@stud.fit.vutbr.cz                    <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the DasboardWidget class.
 **/

#include "device_widget.h"
#include "ui_device_widget.h"
#include "dashboard_controller.h"

unsigned DeviceWidget::WIDGET_EDGE = 250;

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
        QPalette palette;
        palette.setColor(QPalette::Window, Qt::black);
        set_color(palette);
    } 
    else if (_type == DeviceType::CAM)
    {
        set_image(QImage(":/images/cam.png"));
    } 
    else if (_type == DeviceType::HYGR || _type == DeviceType::THERMOMETR || _type == DeviceType::WATT)
    {
        _image = new QImage(WIDGET_EDGE, WIDGET_EDGE, QImage::Format_RGB16);
        _painter = new QPainter(_image);
        _painter->setRenderHint(QPainter::Antialiasing);
        _painter->setPen(QPen(Qt::blue, 3));
        set_chart(Qt::GlobalColor::lightGray);
    } 
    else
    {
        _image = new QImage(WIDGET_EDGE, WIDGET_EDGE, QImage::Format_RGB16);
        _painter = new QPainter(_image);
        _painter->setRenderHint(QPainter::Antialiasing);
        _painter->setPen(QPen(Qt::black, 1));
        _painter->setFont(QFont("Times", 12, QFont::Bold));
        set_chart(Qt::GlobalColor::white);
    }
}

DeviceWidget::~DeviceWidget()
{   
    if (_painter != nullptr)
    {
        _painter->end();
    }
    delete _painter;
    delete _image;
    delete _ui;
}

void DeviceWidget::set_image(QImage image)
{
    Log::log("setting an image");
    _ui->icon->clear();
    QPixmap pix_img = QPixmap::fromImage(image);
    _ui->icon->setPixmap(pix_img.scaled(WIDGET_EDGE, WIDGET_EDGE, Qt::KeepAspectRatio));
    _ui->icon->setVisible(true);
}

void DeviceWidget::set_color(QPalette color)
{
    _ui->icon->clear();
    _ui->icon->setAutoFillBackground(true);
    _ui->icon->setPalette(color);
    _ui->icon->setMinimumSize(WIDGET_EDGE, WIDGET_EDGE);
    _ui->icon->setMaximumSize(WIDGET_EDGE, WIDGET_EDGE);
}

void DeviceWidget::set_description(QString text)
{
    _ui->description->setText(text);
}

void DeviceWidget::set_chart(TreeItem &topic_item)
{
    _image->fill(Qt::GlobalColor::lightGray);
    unsigned size = topic_item.getMessages().size();
    if (size < 2)
    {
        return;
    }
    unsigned step = WIDGET_EDGE / (size - 1);

    std::vector<float> values;
    
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();
    for (unsigned i = 0; i < size; i++)
    {
        QVariant variant = std::get<0>(topic_item.getMessages()[i]);
        std::string string_data = variant.toString().toStdString();
        size_t pos = string_data.find(' ');
        if (pos == std::string::npos)
        {
            pos = string_data.find('%');
        }
        try
        {
            values.push_back(std::stof(string_data.substr(0, pos)));
        }
        catch (const std::exception &e)
        {
            (void)e;
            continue;
        }
        if (values[i] < min)
        {
            min = values[i];
        }
        
        if (values[i] > max)
        {
            max = values[i];
        }
    }

    if (max <= min)
    {
        _painter->drawLine(QPoint(0, WIDGET_EDGE >> 1), QPoint(WIDGET_EDGE, WIDGET_EDGE >> 1));
        
    }
    else
    {
        float scale = WIDGET_EDGE / (max - min + 0.2f);

        for (unsigned i = 1; i < values.size(); i++)
        {
            _painter->drawLine(QPoint((i-1) * step, WIDGET_EDGE - (0.1f + values[i - 1] - min) * scale), 
                               QPoint(i * step, WIDGET_EDGE - (0.1f + values[i] - min) * scale));
        }
    }

    QPixmap pix_img = QPixmap::fromImage(*_image);
    _ui->icon->setPixmap(pix_img.scaled(WIDGET_EDGE, WIDGET_EDGE, Qt::KeepAspectRatio));
    _ui->icon->setVisible(true);
}

void DeviceWidget::set_chart(Qt::GlobalColor color)
{
    _image->fill(color);
    QPixmap pix_img = QPixmap::fromImage(*_image);
    _ui->icon->setPixmap(pix_img.scaled(WIDGET_EDGE, WIDGET_EDGE, Qt::KeepAspectRatio));
    _ui->icon->setVisible(true);
}

void DeviceWidget::set_text(TreeItem &topic_item)
{
    _image->fill(Qt::GlobalColor::white);
    QString text = "";
    QString new_line = "";

    for (int i = topic_item.getMessages().size() - 1; i > 0; i--)
    {
        QVariant variant = std::get<0>(topic_item.getMessages()[i]);
        QString type = std::get<1>(topic_item.getMessages()[i]);
        text.append(new_line + variant.toString());
        new_line = "\n";
    }

    _painter->drawText(_image->rect(), Qt::TextWordWrap, text);
    QPixmap pix_img = QPixmap::fromImage(*_image);
    _ui->icon->setPixmap(pix_img.scaled(WIDGET_EDGE, WIDGET_EDGE, Qt::KeepAspectRatio));
    _ui->icon->setVisible(true);
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
