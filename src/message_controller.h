
#pragma once

#include <tree_item.h>
#include <QVector>
#include <QList>
#include <QBuffer>
#include <QByteArray>

#include <string>

#include "log.h"
#include "json/json-forwards.h"
#include "json/json.h"
#include "client.h"
#include "main_widget_model.h"
#include "tree_model.h"

class MessageController
{
    public:
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);
        static void on_publish_success_cb(void *object, const mqtt::token &token);
        static void on_publish_failure_cb(void *object, const mqtt::token &token);
        static void on_delivery_complete_cb(void *object, mqtt::delivery_token_ptr token);

    private:
        TreeModel *_tree_model = nullptr;
        MainWidgetModel *_main_widget_model = nullptr;
        Client *_client = nullptr;

        QVector<TreeItem *> _topics;
    
        std::vector<std::string> parse_topic_path(std::string path);
        TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);
        TreeItem& add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data);
        TreeItem *create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root);
        TreeItem *get_topic(std::string topic_path);

        void parse_json_message(Json::Value *root, std::string &parsed_string);

    public:
        MessageController(TreeModel *tree_model, MainWidgetModel *main_widget_model);
        ~MessageController() = default;

        void register_client(Client *client);

        void publish(const std::string &topic, const std::string &message);

        void on_message_arrived(const std::string &topic, const MessageData &message, FileType type);
        void on_publish_success(const mqtt::token &token);
        void on_publish_failure(const mqtt::token &token);
        void on_delivery_complete(mqtt::delivery_token_ptr token);
};
