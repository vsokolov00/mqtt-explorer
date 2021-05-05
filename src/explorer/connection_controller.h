
/**
 * @file        connection_controller.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     David Mihola, xmihol00@stud.fit.vutbr.cz; 
 *              Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages connecting to a mqtt broker. 
 *              Declarations of callback types and objects.
 **/

#pragma once

#include <QObject>

#include <string>
#include <thread>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"

using CBObject = void *;
using ConnectCB = void(*)(void *, const std::string&, const std::string&, const mqtt::connect_options&);
using DisconnectCB = void(*)(void *);

/**
 * @brief Used for connecting to a MQTT client.
 **/
class ConnectionController : public QObject
{
    Q_OBJECT

    public:
        /**
         * @brief Callback function called when connection succeeds.
         * @param object user defined object, which will be casted to a ConnectionController class object.
         * @param cause the cause of a successful connection.
         **/
        static void on_connection_success_cb(void *object, const std::string &cause);

        /**
         * @brief Callback function called when connection fails.
         * @param object user defined object, which will be casted to a ConnectionController class object.
         * @param token holds an information about the failed connection.
         **/
        static void on_connection_failure_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when disconnection succeeds.
         * @param object user defined object, which will be casted to a ConnectionController class object.
         * @param token holds an information about the successful disconnection.
         **/
        static void on_disconnection_success_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when disconnection fails.
         * @param object user defined object, which will be casted to a ConnectionController class object.
         * @param token holds an information about the failed disconnection.
         **/
        static void on_disconnection_failure_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when connection is lost.
         * @param object user defined object, which will be casted to a ConnectionController class object.
         * @param cause the cause of the disconnection. 
         **/
        static void on_connection_lost_cb(void *object, const std::string &cause);

    private:
        std::mutex *_mutex;           ///< mutex used for synchronization of operations on the @see _client.
        Client *_client;              ///< the MQTT client used for recieving and publishing messages.

        CBObject _connection_object = nullptr;      ///< user defined object used for callbacks
        ConnectCB _connection_cb = nullptr;         ///< callback function used when connection succeeds
        DisconnectCB _disconnect_cb = nullptr;      ///< callback function used when connection fails

        mqtt::connect_options _connection_options;  ///< connection options specifying the connection to a MQTT client
        bool _reconnect = false;                    ///< true when the connection controller engages a client reconnect
        bool _connection_status = false;            ///< current connection status, true if connected

    public:
        ConnectionController(std::mutex *mutex, CBObject connection_object, ConnectCB connection_cb, DisconnectCB disconnect_cb);
        ~ConnectionController() = default;

        /**
         * @brief Registers a client, on which connection and disconnection operations are made.
         * @param client the registered client
         **/
        void register_client(Client *client);

        /**
         * @brief Gets the current connection status.
         * @return true when connected, otherwise false.
         **/
        bool get_connection_status();

        /**
         * @brief Called when connection is successful.
         * @param cause the cause of the successful connection.
         **/
        void on_connection_success(const std::string &cause);

        /**
         * @brief Called when connection fails.
         * @param token holds an information about the failed connection.
         **/
        void on_connection_failure(const mqtt::token &token);
        
        /**
         * @brief Called when disconnection is successful.
         * @param token holds an information about the successful disconnection.
         **/
        void on_disconnection_success(const mqtt::token &token);

        /**
         * @brief Called when disconnection fails.
         * @param token holds an information about the failed disconnection.
         **/
        void on_disconnection_failure(const mqtt::token &token);

        /**
         * @brief Called when connection is lost.
         * @param cause the cause of the lost connection.
         **/
        void on_connection_lost(const std::string &cause);

        /**
         * @brief Connects the registered @see register_client MQTT client to a broker.
         * @param server_address the adress and port of the broker to which the client is connected.
         * @param id the identification of the connection.
         * @param user_name the user name.
         * @param password the password.
         * @param clean_session true when the session is clean, otherwise false.
         **/
        void connect(const std::string &server_address, const std::string &id, const std::string &user_name, 
                     const std::string &password, bool clean_session);
        
        /**
         * @brief Disconnects the registered @see register_client MQTT client from the broker
         **/
        void disconnect();

        /**
         * @brief Reconnescts the registered @see register_client MQTT client from the broker
         **/
        void reconnect();

        /**
         * @brief Switches from the main window to the login window
         **/
        void go_to_login_view();

    signals:
        /**
         * @brief Emits a signal registered by the main window @see MainView to inform about lost connestion.
         **/
        void connection_lost();

        /**
         * @brief Emits a signal registered by the main window @see MainView to inform about failed reconnection.
         * @param connection_exist true when a connection already exsit on a MQTT broker
         * @param server_address the address of the MQTT broker.
         **/
        void reconnect_failed(bool connection_exist, const std::string &server_address);

        /**
         * @brief Emits a signal registered by the main window @see MainView to inform about failed reconnection.
         **/
        void reconnect_failed();

        /**
         * @brief Emits a signal registered by the login window @see LoginView to inform about failed connection.
         **/
        void connection_failed();

        /**
         * @brief Emits a signal registered by the login window @see LoginView to inform about failed connection.
         **/
        void connection_failed(QString, bool);

        /**
         * @brief Emits a signal registered by the login window @see LoginView to inform about successful connection.
         **/
        void connection_success();
};
