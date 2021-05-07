
/**
 * @file        dashboard_view.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages the dashboard window and its user interface. 
 **/

#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <map>

#include "new_device_dialog.h"
#include "delete_device_dialog.h"
#include "flowlayout.h"
#include "log.h"
#include "dashboard_controller.h"

class DashboardController;

/**
 * @brief manages the Dashboard window.
 **/
class DashboardView : public QWidget
{
    Q_OBJECT

private:
    DashboardController *_dashboard_controller = nullptr;   ///< controlls the dashboard view
    FlowLayout *_flow_layout = nullptr;                     ///< layout of QT widgets
    NewDeviceDialog *_add_dialog = nullptr;                 ///< window for selecting new device
    DeleteDeviceDialog *_delete_dialog = nullptr;           ///< window for deleting devices
    QVBoxLayout *_central_layout = nullptr;                 ///< dashboard layout
    QPushButton *_add_device = nullptr;                     ///< add device button
    QPushButton *_delete_device = nullptr;                  ///< delete device button

private slots:
    /**
     * @brief Triggered when "add device" button is pressed.
     **/
    void on_add_device_clicked();

    /**
     * @brief Triggered when "delete device" button is pressed
     **/
    void on_delete_device_clicked();

    /**
     * @brief adds and displays new device.
     * @param name the name of the device.
     * @param topic the topic on which the devic is located.
     * @param device_type the type of the device.
     **/
    void add_device(QString name, QString topic, unsigned device_type);
public slots:
    /**
     * @brief delete_devices Deletes devies from the flow layout and dashboard controller
     */
    void delete_devices(std::vector<int>);

public:
    DashboardView(DashboardController *dashboard_controller, FlowLayout *flow_layout);
    ~DashboardView();

};
