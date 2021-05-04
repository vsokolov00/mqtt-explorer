
/**
 * @file        reciever.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a Reciever class.
 **/

#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>

#include "parser.h"
#include "base_device.h"
#include "../client/client.h"
#include "../client/listener.h"
#include "options.h"
#include "log.h"

/**
 * @brief Recieves all messages on topics subscribed by recieving devices, finds the devices to which the mesage
 *        belongs and forwards the message to the device. The devices are registered based on their subscription
 *        topic and id into a map and must have a @see RecievingDevice class as a base class.
 **/
class Reciever
{
    public:
        /**
         * @brief A callback function passed to the client, which is called when connection of the client succeeds.
         * @param object a user defined Reciever object of the registered callback, on which the @see on_connected
         *               function called.
         * @param cause the cause of the callback.
         **/
        static void on_connection_success_cb(void *object, const std::string &cause);

        /**
         * @brief A callback function passed to the client, which is called when a new message arrives.
         * @param object a user defined Reciever object of the registered callback, on which the 
         *               @see on_message_arrived function called.
         * @param cause the cause of the callback.
         **/
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);

        /**
         * @brief A callback function passed to the client, which is called when connection to a server is lost.
         * @param object a user defined Reciever object of the registered callback, on which the 
         *               @see on_connection_lost function called.
         * @param cause the cause of the callback.
         **/
        static void on_connection_lost_cb(void *object, const std::string &cause);

        /**
         * @brief A dummy callback for delivery complete, it is not important if the message arrives.
         * @param object dummy
         * @param cause dummy.
         **/
        static void on_delivery_complete_dummy_cb(void *object, mqtt::delivery_token_ptr token);

        /**
         * @brief A dummy operation success/failure callback used for operation which are not important such as disconnect.
         * @param object dummy
         * @param cause dummy.
         **/
        static void dummy_cb(void *object, const mqtt::token &token);

        /**
         * @brief A callback function passed to the client, which is called when connection to a server fails.
         * @param object a user defined Reciever object of the registered callback, on which the 
         *               @see on_connection_failure function called.
         * @param cause the cause of the callback.
         **/
        static void on_connection_failure_cb(void *object, const mqtt::token &token);

        /**
         * @brief A callback function passed to the client, which is called when subscription of a topic succeeds.
         * @param object a user defined Reciever object of the registered callback, on which the 
         *               @see on_subscribe_success function called.
         * @param cause the cause of the callback.
         **/
        static void on_subscribe_success_cb(void *object, const mqtt::token &token);

        /**
         * @brief A callback function passed to the client, which is called when subscription of a topic fails.
         * @param object a user defined Reciever object of the registered callback, on which the 
         *               @see on_subscribe_failure function called.
         * @param cause the cause of the callback.
         **/
        static void on_subscribe_failure_cb(void *object, const mqtt::token &token);
    
    private:
        std::unordered_map<std::string, RecievingDevice *> _map;       ///< stores topic+id device pairs used for forwarding recieved messages 
        std::vector<std::string> _topics;                              ///< subscribed topics, which are monitored
        Client _client;                                                ///< Client used for recieving and sending messages
        std::mutex *_mutex;                                            ///< mutex for synchronization of operations on the @see _client

        /**
         * @brief Reacts to a connection to a server success. Subscribes to registered topics by the devices.
         * @param cause the cuase of successful connection
         **/
        void on_connected(const std::string &cause);

        /**
         * @brief Reacts to an arrived message, which is parsed (must be a JSON format, filtered already by the client) 
         *        and forwarded to a device specified by the topic on which the message arrived and the parsed device id.
         * @param topic the topic on which the message arrived.
         * @param root the root element of the arrived JSON message.
         **/
        void on_message_arrived(const std::string &topic, const Json::Value &root);

        /**
         * @brief Reacts to a lost connection to a server.
         * @param cause the cuase of successful connection
         **/
        void on_connection_lost(const std::string &cause);

        /**
         * @brief Reacts to a failed connection to a server.
         * @param token the token describing the reason of the failure.
         **/
        void on_connection_failure(const mqtt::token &token);

        /**
         * @brief Reacts to a successful subscription of a topic.
         * @param token the token describing the sucessfuly subscribed topic.
         **/
        void on_subscribe_success(const mqtt::token &token);

        /**
         * @brief Reacts to a failed subscription of a topic.
         * @param token the token describing the failed subscription of the topic.
         **/
        void on_subscribe_failure(const mqtt::token &token);

        /**
         * @brief A template function fro registering devices with base class @see RecievingDevice.
         * @param devies a recieving device of type T.
         **/
        template<typename T> void register_device(std::vector<T> &device);

    public:
        Reciever(const std::string &server_address, const std::string &id);
        Reciever(const Reciever&) = delete;
        ~Reciever();

        /**
         * @brief Registers all devices with base class @see RecievingDevice.
         * @param devices the devices to be registered.
         * @param flags the flags specified by the command line argumenst, which specifies which devices should be registered.
         **/
        void regiser_devices(Devices &devices, unsigned flags);

        /**
         * @brief Connect the client and starts recieving.
         * @param conenction_options the options of the connection.
         * @return true on failure otherwise false
         **/
        bool start_recieving(const mqtt::connect_options &connect_options);

        /**
         * @brief Disonnect the client and stops recieving.
         * @return true on failure otherwise false
         **/
        bool stop_recieving();
};
