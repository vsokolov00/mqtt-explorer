
/**
 * @file        program.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz                    <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages all resources of the application and provides them
 *              to specific controllers, views and models.
 **/

#pragma once

#include <QApplication>
#include <thread>
#include <fstream>
#include <sstream>

#include "log.h"

#include "../json/json/json.h"
#include "../json/json/json-forwards.h"
#include "../client/client.h"
#include "../client/listener.h"

#include "tree_model.h"

#include "main_view.h"
#include "login_view.h"
#include "dashboard_view.h"

#include "connection_controller.h"
#include "message_controller.h"
#include "subscription_controller.h"
#include "dashboard_controller.h"
#include "flowlayout.h"

/**
 * @brief Holds all models, views and controllers and a client. Provides them to other objects which need them
 *        and manages the run of the application.
 **/
class Program
{
    private:
        static std::string CONFIG_FILE;

    public:
        /**
         * @brief Connection callback called when connection should be established.
         * @param object user defined object which is casted to Program class object.
         * @param server_adress address of the MQTT broker to connect to.
         * @param id the id of the connection.
         * @param connection_options the options of the client connection to the MQTT broker.
         **/
        static void connect_cb(void *object, const std::string &server_address, const std::string &id, 
                                          const mqtt::connect_options &connection_options);

        /**
         * @brief Disconenction callback called when disconetion should be managed.
         * @param object user defined object which is casted to Program class object.
         **/
        static void disconnect_cb(void * object);


    private:
        Client *_client = nullptr;              ///< MQTT client
        TreeModel *_tree_model = nullptr;       ///< main data model of the application

        DashboardView *_dashboard_view = nullptr;
        LoginView *_login_view = nullptr;
        MainView *_main_view = nullptr;

        ConnectionController *_connection_controller = nullptr;
        MessageController *_message_controller = nullptr;
        SubscriptionController *_subscription_controller = nullptr;
        DashboardController *_dashboard_controller = nullptr;

        FlowLayout *_flow_layout = nullptr;

        std::mutex *_mutex;

        void load_configuration();
        void save_configuration();

    public:
        Program() = default;
        ~Program();
        Program(const Program&) = delete;

        /**
         * @brief Initilizes the program.
         **/
        void init();

        /**
         * @brief Starts the program.
         **/
        void start();

        /**
         * @brief Stops the program.
         **/
        void quit();

        /**
         * @brief Connects the client to a MQTT broker.
         * @param server_adress address of the MQTT broker to connect to.
         * @param id the id of the connection.
         * @param connection_options the options of the client connection to the MQTT broker.
         **/
        void connect(const std::string &server_address, const std::string &id, 
                     const mqtt::connect_options &connection_options);

        /**
         * @brief Disconects the client from a MQTT broker.
         **/
        void disconnect();
};
