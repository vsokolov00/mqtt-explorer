
#pragma once

#include <treeitem.h>
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
