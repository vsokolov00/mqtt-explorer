
/**
 * @file        main_view.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class used to control the main window of the application.
 **/

#pragma once

#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
#include <QBuffer>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"
#include "popup.h"

#include "tree_model.h"
#include "dashboard_view.h"

#include "connection_controller.h"
#include "message_controller.h"
#include "subscription_controller.h"
#include "dashboard_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Manages the main window user interface.
 **/
class MainView : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_publish_clicked();      ///< triggered when "publish" button is pressed
    void on_subscribe_clicked();    ///< triggered when "subscribe" button is pressed
    void on_unsubscribe_clicked();  ///< triggered when "unsubscribe" button is pressed
    void on_chooseFile_clicked();   ///< triggered when "chose file" button is pressed
    void on_clear_clicked();        ///< triggered when "clear" button is pressed

    void on_disconnect_clicked();   ///< triggered when "disconnect" button is pressed

    void on_save_snapshot_clicked();    ///< triggered when "save snapshot" button is pressed

    void on_dashboard_clicked();        ///< triggered when "dashboard" button is pressed
signals:
    void dashboard_opened();        ///< Informs that the dashboard is open.

private:
    Ui::MainWindow *_ui = nullptr;      ///< the main window user interface

    TreeModel *_tree_model = nullptr;   ///< three model for managing message tree structure

    ConnectionController *_connection_controller = nullptr;         ///< controller managing connection to a MQTT broker
    MessageController *_message_controller = nullptr;               ///< controller managing publish and recieval of messages
    SubscriptionController *_subscription_controller = nullptr;     ///< controller managing subscription/unsubscription to a topic
    DashboardController *_dashboard_controller = nullptr;           ///< controller managing the dasboard

    PopUp* _pop_up;          ///< manages pop ups displaying messages

    /**
     * @brief Shows a pop up with a message about an operation which was successful/unsuccessful.
     **/
    void show_popup();

public:
    MainView(TreeModel *tree_model, ConnectionController *connection_controller,
            MessageController *message_controller, SubscriptionController *subscription_controller, 
            DashboardController *dashboard_controller);
    ~MainView();

    /**
     * @brief Selects a message in a history of a topic.
     **/
    void item_selection();

    /**
     * @brief Displays the main window
     **/
    void display();

public slots:
    void publish_success_popup_set();                     ///< Triggerd when publish of a message is successful.
    void publish_failure_popup_set();                     ///< Triggerd when publish of a message is fails.

    /**
     * @brief Tgriggered when a subscription to a topic succeeds.
     * @param s the topic.
     **/
    void subscribe_success_popup_set(QString s);

    /**
     * @brief Tgriggered when a subscription to a topic fails.
     * @param s the topic.
     **/
    void subscribe_failure_popup_set(QString s);
    /**
     * @brief Tgriggered when a unsubscription of a topic succeeds.
     * @param s the topic.
     **/
    void unsubscribe_success_popup_set(QString s);

    /**
     * @brief Tgriggered when an unsubscription of a topic fails.
     * @param s the topic.
     **/
    void unsubscribe_failure_popup_set(QString s);

    void connection_lost_dialog();                      ///< Triggered when connection to a MQTT broker is lost.
    void reconnection_failed_dialog();                  ///< Triggered when reconnection to a MQTT broker fails.
    void connection_failure_popup_set(QString, bool);   ///< Triggered when connection to a MQTT broker fails.
    void connection_failure_popup_set();                ///< Triggered when connection to a MQTT broker fails.
    void connection_success_popup_set();                ///< Triggered when connection to a MQTT broker succeeds.
    void display_full_message(QListWidgetItem*);        ///< Triggered when a message in separate window is shown.
};
