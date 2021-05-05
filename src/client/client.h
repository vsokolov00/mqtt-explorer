
/**
 * @file        client.h                                                                 
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Declaration of types and classes for client.cpp and other files.
 **/

#pragma once

#include "../json/json/json.h"
#include "../json/json/json-forwards.h"
#include "listener.h"

#include <string>
#include <thread>
#include <mqtt/client.h>

/**
 * @enum File types that can be parsed by the client API and registered by the user of the client API. 
 **/
enum class FileType : unsigned short 
{
    BINARY = 0b1,
    STRING_UTF8 = 0b10,
    JSON = 0b100,
    JPG = 0b1000,
    PNG = 0b10000,
    ALL_IMAGES = 0b111100,
    ALL = 0b111111,
    AS_BINARY = 0b1000000,
    ALL_AS_BINARY = 0b1111111
};

using ParsingLevel = unsigned short;

/**
 * @brief Used for forwarding parsed text messages.
 **/
struct String
{
    size_t size;        ///< size of a text data
    const char *data;   ///< data of the text message
};

/**
 * @brief Used for forwarding parsed binary messages including images.
 **/
struct Binary
{
    size_t size;        ///< size of a binary data
    const char *data;   ///< binary data of the message
};

/**
 * @brief Used to forward messages of different format.
 **/
union MessageData
{
    String string;      ///< text message
    Binary binary;      ///< binary message
    Json::Value *json;  ///< parsed JSON message
};

using OnConnectionSuccessCB = void(*)(void *, const std::string&);
using OnMessageArrivedCB = void(*)(void *, const std::string&, const MessageData&, FileType);
using OnConnectionLostCB = void(*)(void *, const std::string&);
using OnDeliveryCompleteCB = void(*)(void *, mqtt::delivery_token_ptr);

/**
 * @brief Represents an API to the mqtt client
 **/
class Client : public virtual mqtt::callback
{
    private:
        /// files types of recieved message
        static const ParsingLevel BINARY;
        static const ParsingLevel STRING;
        static const ParsingLevel JSON;
        static const ParsingLevel JPG;
        static const ParsingLevel PNG;
        static const ParsingLevel ALL_IMAGES;
        static const ParsingLevel AS_BINARY;

    public:
        /**
         * @brief Adds a file type to a level of message parsing.
         * @param current_levels the current level of message parsing.
         * @param file_type the new file type to be added.
         **/
        static void add_parsing_level(ParsingLevel &current_levels, FileType file_type);

        /**
         * @brief Removes a file type to a level of message parsing.
         * @param current_levels the current level of message parsing.
         * @param file_type the removed file type to be added.
         **/
        static void remove_parsing_level(ParsingLevel &current_levels, FileType file_type);
    
    private:
        /**
         * @brief A dummy callback.
         **/
        static void dummy_cb(void *object, const mqtt::token& token);

    private:
        /**
         * @brief Called when the client connects.
         * @param cause the cause of the successful connection.
         **/
        void connected(const std::string &cause) override;

        /**
         * @brief Called when the client loses connections.
         * @param cause the cause of the lost connection.
         **/
        void connection_lost(const std::string &cause) override;

        /**
         * @brief Called when the client recieves a message.
         * @param msg the arrived message.
         **/
        void message_arrived(mqtt::const_message_ptr msg) override;

        /**
         * @brief Called when the publish of a message is copleted.
         * @param token the token representin the publish message.
         **/
        void delivery_complete(mqtt::delivery_token_ptr token) override;

        mqtt::async_client _client;                         ///< the mqtt client
        ParsingLevel _level;                                ///< the selected file parsing level

        void *_connection_object;                           ///< callback object used for connection results
        OnConnectionSuccessCB _connection_success_cb;       ///< callback on connection success
        OnConnectionLostCB _connection_lost_cb;             ///< callback on connection lost
        Listener _connect_listener;                         ///< connection listener, which holds the connection callbacks
        Listener _disconect_listener;                       ///< disconnection listener, which holds the desconnection callbacks

        void *_message_object;                              ///< callback object used for message arrival and message publish
        OnMessageArrivedCB _message_arrived_cb;             ///< callback when on message arrives
        OnDeliveryCompleteCB _delivery_complete_cb;         ///< callback when on a message delivery complete 
        Listener _publish_listener;                         ///< publish listener, which holds publish callbacks

        Listener _subscribe_listener;                       ///< subscription listener used for subscription callbacks
        Listener _unsubscribe_listener;                     ///< unsubscription listener used for unsubscription callbacks

        Json::CharReader *_reader;                          ///< jsoncpp JSON file parses
        std::mutex *_muttex;                                ///< synchronization muttex

    public:
        Client(const std::string server_address, const std::string &id, FileType single_file_type,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const std::string server_address, const std::string &id, ParsingLevel level,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb);

        Client(const Client&) = delete;
        ~Client();
        
        /**
         * @brief Connects the client.
         * @param connect_options the options of connection of the client.
         * @return false on success, otherwise true.
         **/
        bool connect(const mqtt::connect_options &connect_options);

        /**
         * @brief Disconnects the client.
         * @return false on success, otherwise true.
         **/
        bool disconnect();

        /**
         * @brief Subscribes to a new topic.
         * @param topic the subscribed topic.
         * @param QOS the quality of service on the subscribed topic.
         **/
        void subscribe(const std::string topic, const int QOS);

        /**
         * @brief Unubscribes to a topic.
         * @param topic the unsubscribed topic.
         **/
        void unsubscribe(const std::string topic);

        /**
         * @brief Publishes a new message to given topic.
         * @param topic the topic of the publish message.
         * @param message the published message.
         **/
        int publish(const std::string topic, const std::string message);
};
