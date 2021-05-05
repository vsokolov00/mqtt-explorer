
/**
 * @file        dashboard_controller.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages the logic of the dasboard window. 
 **/

#pragma once

#include <QObject>
#include "device_widget.h"
#include "log.h"

class DashboardView;

/**
 * @brief Manages the dashboard view @see DashboardView.
 **/
class DashboardController : public QObject
{
    Q_OBJECT

private:
    DashboardView *_dashboard_window = nullptr;     ///< dashboard window

public:
    std::map<std::string, DeviceWidget*> topic_to_device;

    explicit DashboardController(QObject *parent = nullptr);
    ~DashboardController();

    /**
     * @brief Registers a dahboard view.
     * @param dashboard_window the dashboard view.
     **/
    void register_dashboard_view(DashboardView *dashboard_window);

    /**
     * @brief Adds a new device to the dashboard.
     * @param device the newly added device.
     **/
    void add_device(DeviceWidget* device);

    /**
     * @brief processes and displays new messages, if it belong to any device on the dashboard.
     * @param topic the topic of the message.
     * @param paload the data of the message.
     **/
    void process_message(std::string topic, QByteArray payload);

    /**
     * @brief Displays the dashboard.
     **/
    void show_dashboard();

signals:
    /**
     * @brief Informs about a new device on a given topic.
     * @param device the new device.
     **/
    void new_device_on_topic(std::string topic);
};
