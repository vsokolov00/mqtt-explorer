
/**
 * @file        message_controller.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     David Mihola, xmihol00@stud.fit.vutbr.cz; 
 *              Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which manages message recieval and publish from and to a mqtt broker. 
 **/

#pragma once

#include <tree_item.h>
#include <QVector>
#include <QList>
#include <QBuffer>
#include <QByteArray>
#include <QBrush>
#include <QItemSelectionModel>
#include <QJsonDocument>
#include <QDir>

#include <string>
#include <unordered_map>

#include "log.h"
#include "../json/json/json-forwards.h"
#include "../json/json/json.h"
#include "tree_model.h"
#include "dashboard_controller.h"

/**
 * @brief Used for recieving and publishing messages to and from a MQTT broker.
 **/
class MessageController : public QObject
{
    Q_OBJECT

    public:
        /**
         * @brief Callback function called when message arrives.
         * @param object user defined object, which will be casted to a MessageController class object.
         * @param topic the topic on which the message arrived.
         * @param message the arrived message.
         * @param type the type of the message. 
         **/
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);

        /**
         * @brief Callback function called when publish of a message succeeds.
         * @param object user defined object, which will be casted to a MessageController class object.
         * @param token token holding information about the published message.
         **/
        static void on_publish_success_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when publish of a message fails.
         * @param object user defined object, which will be casted to a MessageController class object.
         * @param token token holding information about the published message.
         **/
        static void on_publish_failure_cb(void *object, const mqtt::token &token);

        /**
         * @brief Callback function called when delivery of a message is completed.
         * @param object user defined object, which will be casted to a MessageController class object.
         * @param token token holding information about the delivered message.
         **/
        static void on_delivery_complete_cb(void *object, mqtt::delivery_token_ptr token);

    private:
        TreeModel *_tree_model = nullptr;               ///< model used for storing recieved messages
        Client *_client = nullptr;                      ///< MQTT client used for recieving and publishing messages

        QVector<TreeItem *> _root_topics;               ///< root topics of the model @see _tree_model

        /**
         * @brief Key, value pairs representing hashed message and a true when the message was published by our client,
         *        otherwise false.
         **/
        std::map<std::size_t, bool> _message_map;

        bool _file_chosen = false;      ///< true when a file to publish is chosen
        QVariant _file_to_publish;      ///< data of published file
        FileType _file_type;            ///< type of recieved message.

        bool _dashboard_is_opened = false;              ///< true when the dashboard is open
        DashboardController* _dashboard_controller;     ///< controls the dashboard view

        /**
         * @brief Parses a topic to seperate subtopics.
         * @param path the topic
         * @return the parsed root topic and subtopics.
         **/    
        std::vector<std::string> parse_topic_path(std::string path);

        /**
         * @brief Finds an tree item representing a searched topic.
         * @param name the topic name
         * @param topics available topics.
         * @return found tree item, otherwise nullptr
         **/
        TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);

        /**
         * @brief Adds a subtopic to a topic tree.
         * @param supertopic the parent topic of the newly added topic.
         * @param topic_name the name of the newly added topic.
         * @param data the first recieved message on that topic.
         **/
        TreeItem& add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data);

        /**
         * @brief Created a topic hierarchy. 
         * @param supertopic the parent topic of the hierarchy.
         * @param topics the the newly added topics.
         * @param new_root true when new root is created otherwise false.
         **/
        TreeItem *create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root);

        /**
         * @brief Gets a topic matching specified topic path.
         * @param topic_path the topic path (i.e. the topic).
         * @return the tree item representing the topic.
         **/
        TreeItem *get_topic(std::string topic_path);

        /**
         * @brief Hashes a message.
         * @param data the data of a message.
         * @param size the size of a message.
         * @return the corresponding hashed value of the message.
         **/
        size_t hash_function(const char *data, size_t size);

    public:
        MessageController(TreeModel *tree_model, DashboardController* dbcon);
        ~MessageController() = default;

        /**
         * @brief Registers a client which is used for recieving and publishing messages.
         * @param client the registered client.
         **/
        void register_client(Client *client);

        /**
         * @brief Validates a topic path.
         * @param path the path of the topic.
         * @return the validated topic path without trailing '/'.
         **/
        QString validate_topic_path(QString path);

        /**
         * @brief Publishes an MQTT message.
         * @param topic the topic on which the message is published.
         * @param message the published message.
         **/
        void publish(const std::string &topic, const std::string &message);

        /**
         * @brief Called when message arrives.
         * @param topic the topic on which the message arrived.
         * @param message the recieved message.
         * @param type the type of the recieved message.
         **/
        void on_message_arrived(const std::string &topic, const MessageData &message, FileType type);

        /**
         * @brief Called when publish of a message is successful.
         * @param token token holding information about the successful publish.
         **/
        void on_publish_success(const mqtt::token &token);

        /**
         * @brief Called when publish of a message fails.
         * @param token token holding information about the failed publish.
         **/
        void on_publish_failure(const mqtt::token &token);

        /**
         * @brief Called when a delivery of a message is completed.
         * @param token token holding information about the completed delivery.
         **/
        void on_delivery_complete(mqtt::delivery_token_ptr token);

        /**
         * @brief Sets a file chosen indicating variable @see _file_chosen to true.
         **/
        void set_file_chosen();

        /**
         * @brief Sets a file chosen indicating variable @see _file_chosen to false.
         **/
        void set_file_not_chosen();

        /**
         * @brief Retrieves information whether a file is chosen.
         * @return true when file is chosen, otherwise false.
         **/
        bool is_file_chosen();
        
        /**
         * @brief Sets a content of a current message.
         * @param content the content of the message.
         **/
        void set_message(QVariant content);

        /**
         * @brief Gets the current message.
         * @return the current message.
         **/
        QVariant& get_message();

        /**
         * @brief Retrieves current root topics.
         * @return the root topics.
         **/
        QVector<TreeItem *>& get_root_topics();

        /**
         * @brief Creates a directory structure when snapshot is saved.
         * @param parent_dir the parent directory of the directory structure.
         * @param subtopics the currently existing topics.
         **/
        void create_dir_structure(QDir parent_dir, QVector<TreeItem *>& subtopics);

    public slots:
        void dashboared_opened();
        void dashboared_closed();
        
    signals:
        /**
         * @brief Emits a signal registered by the main window @see MainView informing about successful publish.
         **/
        void publish_success();

        /**
         * @brief Emits a signal registered by the main window @see MainView informing about unsuccessful publish.
         **/
        void publish_failure();

        /**
         * @brief Emits a signal registered by the main window @see MainView informing when new message arrives.
         **/
        void message_arrived();
};
