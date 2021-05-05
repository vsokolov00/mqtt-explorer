
/**
 * @file        new_device_dialog.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages a window for adding new devices to the dasboard. 
 **/

#pragma once

#include <QDialog>

namespace Ui {
class NewDeviceDialog;
}

/**
 * @brief Displays a window where a new device for the dasboard can be customize.
 **/
class NewDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDeviceDialog(QWidget *parent = nullptr);
    ~NewDeviceDialog();

signals:
    /**
     * @brief Informs that a new device was added.
     * @param name the name of the device.
     * @param topic the topic of the device.
     * @param device_type the type of the device.
     **/
    void new_device_added(QString name, QString topic, unsigned device_type);

private slots:
    /**
     * @brief Triggered when "Add" button was pressed.
     **/
    void on_ok_clicked();

    /**
     * @brief Triggered when "Cancel" button was pressed.
     **/
    void on_cancel_clicked();

private:
    Ui::NewDeviceDialog *_ui;       ///< the user interface of the window
};

