
/**
 * @file        device_widget.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 *              David Mihola, xmihol00@stud.fit.vutbr.cz                    <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages dasboard devices and declaration of device types. 
 **/

#pragma once

#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QLineF>
#include <QJsonDocument>

#include <limits>
#include <vector>

#include "log.h"
#include "tree_item.h"

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

/**
 * @brief Represents one device on the dasboard.
 **/
class DeviceWidget : public QWidget
{
    Q_OBJECT

private:
    static unsigned WIDGET_EDGE;        ///< size of a device widget

    Ui::DeviceWidget *_ui;              ///< widget representing the device data
    DeviceType _type;                   ///< type of a device
    QString _name;                      ///< name of a device
    QString _topic;                     ///< topic on which a device is subscribed
    QPainter *_painter = nullptr;       ///< painter used for plotting data and displaying text
    QImage *_image = nullptr;           ///< image used to paint on

public:
    explicit DeviceWidget(QWidget *parent = nullptr, DeviceType type = DeviceType::ERR, QString name = "Device", QString topic = "");
    ~DeviceWidget();

    /**
     * @brief Gets a type of the device.
     * @return The type of the device.
     **/
    DeviceType get_type();

    /**
     * @brief Gets a name of the device.
     * @return The name of the device.
     **/
    std::string get_name();

    /**
     * @brief Gets a topic of the device.
     * @return The topic of the device.
     **/
    std::string get_topic();

    /**
     * @brief Set the widget to show an image.
     * @param image the image to be displayed.
     * @param width the width of the image.
     * @param height the height of the image.
     **/
    void set_image(QImage image);

    /**
     * @brief Set the widget to show a color.
     * @param color the color.
     **/
    void set_color(QPalette color);

    /**
     * @brief Set the widget to show a text description.
     * @param text the text description.
     **/
    void set_description(QString text);

    /**
     * @brief Sets the widget to show text data.
     * @param topic_item messages on the topic.
     **/
    void set_text(TreeItem &topic_item);

    /**
     * @brief Sets the widget to show a chart.
     * @param topic_item messages on the topic.
     **/
    void set_chart(TreeItem &topic_item);

    /**
     * @brief Sets an empty chart with a base color.
     * @param color the color
     **/
    void set_chart(Qt::GlobalColor color = Qt::GlobalColor::lightGray);
};
