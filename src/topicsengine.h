#ifndef TOPICSENGINE_H
#define TOPICSENGINE_H

#include <treeitem.h>
#include <mqttreemodel.h>
#include <QVector>
#include <QList>

class TopicsEngine
{
public:
    TopicsEngine(TreeModel& m);
    ~TopicsEngine();
    void send_message(std::string topic_path, std::string text_message); //client calls this function when new message arrives
private:
    std::vector<TreeItem*> root_topics;
    int total_topics;

    std::vector<std::string> parse_topic_path(std::string path);

    TreeItem* find_topic(std::string name, std::vector<TreeItem*>&);
    TreeItem* find_topic1(std::string name, const QVector<TreeItem*>& topics);

    TreeItem& add_topic(TreeItem& supertopic, std::string topic_name, QVariant data);
    void create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root, std::string text_message);

private:
    TreeModel& model;
};

#endif // TOPICSENGINE_H
