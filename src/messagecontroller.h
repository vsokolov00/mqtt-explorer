#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <treeitem.h>
#include <mqttreemodel.h>
#include <QVector>
#include <QList>
#include <QBuffer>
#include <QByteArray>

#include <string>

#include "mainwindow.h"
#include "json/json-forwards.h"
#include "json/json.h"
#include "client.h"

/*enum class FileType : short
{
    NONE = -1,
    BINARY = 0,
    STRING_UTF8,
    JSON,
    IMAGE
};*/

class MessageController
{
    public:
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);
        static void on_publish_success_cb(void *object, const mqtt::token &token);
        static void on_publish_failure_cb(void *object, const mqtt::token &token);
        static void on_delivery_complete_cb(void *object, mqtt::delivery_token_ptr token);

    private:
        MainWindow *_main_window;

        void parse_json_message(Json::Value *root, std::string &parsed_string);

    public:
        MessageController(MainWindow *main_window);
        ~MessageController() = default;

        void on_message_arrived(const std::string &topic, const MessageData &message, FileType type);
        void on_publish_success(const mqtt::token &token);
        void on_publish_failure(const mqtt::token &token);
        void on_delivery_complete(mqtt::delivery_token_ptr token);
};

#endif // MESSAGECONTROLLER_H
