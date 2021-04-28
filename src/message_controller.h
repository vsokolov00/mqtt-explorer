
#pragma once

#include <tree_item.h>
#include <QVector>
#include <QList>
#include <QBuffer>
#include <QByteArray>
#include <QItemSelectionModel>
#include <QJsonDocument>

#include <string>
#include <unordered_map>

#include "log.h"
#include "json/json-forwards.h"
#include "json/json.h"
#include "client.h"
#include "tree_model.h"

class MessageController : public QObject
{
    Q_OBJECT

    public:
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);
        static void on_publish_success_cb(void *object, const mqtt::token &token);
        static void on_publish_failure_cb(void *object, const mqtt::token &token);
        static void on_delivery_complete_cb(void *object, mqtt::delivery_token_ptr token);

    private:
        TreeModel *_tree_model = nullptr;
        Client *_client = nullptr;

        QVector<TreeItem *> _root_topics;

        std::hash<std::string> _string_hash;
        std::map<std::size_t, bool> _message_map;

        bool _file_chosen;
        QVariant _file_to_publish;
        FileType _file_type;
    
        std::vector<std::string> parse_topic_path(std::string path);
        TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);
        TreeItem& add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data);
        TreeItem *create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root);
        TreeItem *get_topic(std::string topic_path);

        bool parse_json_message(const Binary &binary_data, QJsonDocument &json_document);

    public:
        MessageController(TreeModel *tree_model);
        ~MessageController() = default;

        void register_client(Client *client);

        QString validate_topic_path(QString);
        void publish(const std::string &topic, const std::string &message);

        void on_message_arrived(const std::string &topic, const MessageData &message, FileType type);
        void on_publish_success(const mqtt::token &token);
        void on_publish_failure(const mqtt::token &token);
        void on_delivery_complete(mqtt::delivery_token_ptr token);

        void set_file_chosen();
        void set_file_not_chosen();

        void set_message(QVariant, FileType type);
        FileType get_message_type();
        QVariant& get_message();

    signals:
        void publish_success();
        void publish_failure();
        void message_arrived();
};
