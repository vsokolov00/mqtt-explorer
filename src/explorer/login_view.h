
/**
 * @file        login_view.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class used to control the login window of the application.
 **/

#pragma once

#include <QMovie>
#include <QMainWindow>
#include <string>

#include <thread>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"
#include "connection_controller.h"
#include "popup.h"

namespace Ui { class Login; }

class Program;

/**
 * @brief Manages the login window user interface
 **/
class LoginView: public QMainWindow
{
    Q_OBJECT

    private slots:
        void on_connect_clicked();

    private:
        Ui::Login *_ui = nullptr;       ///< the login window user interface

        PopUp* _pop_up;                 ///< manages pop up messages

        ConnectionController *_connection_controller = nullptr;     ///< connection controller managing this view

        /**
         * @brief Displays a message in a pop up.
         **/
        void show_popup();          

    public:
        LoginView(ConnectionController *connection_cotroller);
        ~LoginView();

    public slots:
        /**
         * @brief Sets and displays a pop up informing about failed connection to the MQTT broker.
         **/
        void connection_failure_popup_set();

};
