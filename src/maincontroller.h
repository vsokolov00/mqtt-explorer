#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <treeitem.h>
#include <mqttreemodel.h>
#include <QVector>
#include <QList>
#include <string>
#include <string.h>

enum class FileType : unsigned short
{
    ALL = 0xFFFF,
    BINARY = 0b1,
    STRING_UTF8 = 0b10,
    JSON = 0b100,
    JPG = 0b1000,
    PNG = 0b10000,
    GIF = 0b100000,
    ALL_IMAGES = 0b111100
};

class MainController
{
public:
    MainController(TreeModel& m);
    ~MainController();
    void message_recieved(std::string topic_path, QVariant& data, FileType msgType);
private:
    QVector<TreeItem*> root_topics;
    TreeModel& model;

    std::vector<std::string> parse_topic_path(std::string path);
    TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);
    TreeItem& add_child(TreeItem& supertopic, std::string topic_name, QVariant data);
    void create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root, QVariant& qv);
};

#endif // MAINCONTROLLER_H
