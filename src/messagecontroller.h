#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <treeitem.h>
#include <mqttreemodel.h>
#include <QVector>
#include <QList>
#include <QBuffer>

#include <string>
#include <string.h>
#include <unistd.h>

enum class FileType : short
{
    NONE = -1,
    BINARY = 0,
    STRING_UTF8,
    JSON,
    IMAGE
};

class MessageController
{
public:
    MessageController(TreeModel& m);
    ~MessageController();
    void message_recieved(std::string topic_path, QVariant& data, FileType msg_type);
    bool publish_msg(std::string topic, QVariant msg);

    void set_file_chosen();
    void set_file_not_chosen();

    void set_message(QVariant, FileType type);
    FileType get_message_type();
    QVariant& get_message();
private:
    QVector<TreeItem*> root_topics;
    TreeModel& model;

    bool file_chosen = false;
    QVariant file_to_publish;
    FileType file_type;

    std::vector<std::string> parse_topic_path(std::string path);
    TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);
    TreeItem& add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data);
    void create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root, QVariant& qv, FileType type);
};

#endif // MESSAGECONTROLLER_H
