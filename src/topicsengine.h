#ifndef TOPICSENGINE_H
#define TOPICSENGINE_H

#include <treeitem.h>
#include <mqttreemodel.h>
#include <QVector>
#include <QList>
#include <string>
#include <string.h>

class TopicsEngine
{
public:
    TopicsEngine(TreeModel& m);
    ~TopicsEngine();
    void recieve_message(std::string topic_path, QVariant& data); //client calls this function when new message arrives
private:
    std::vector<TreeItem*> root_topics;
    int total_topics;

    std::vector<std::string> parse_topic_path(std::string path);

    /**
     * @brief TopicsEngine::find_topic checks if the given vector of topics contain a topic with the given name
     * @param name
     * @param topics
     * @return
     */
    TreeItem* find_topic(std::string name, std::vector<TreeItem*>&);
    TreeItem* find_topic1(std::string name, const QVector<TreeItem*>& topics);

    TreeItem& add_child(TreeItem& supertopic, std::string topic_name, QVariant data, std::string path);
    void create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, std::string full_path, bool new_root, QVariant& qv);

private:
    TreeModel& model;
};

#endif // TOPICSENGINE_H
