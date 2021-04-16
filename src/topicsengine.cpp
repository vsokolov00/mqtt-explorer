#include "topicsengine.h"
#include <iostream>

TopicsEngine::TopicsEngine(TreeModel& m)
    : model(m)
{
    root_topics = {};
    total_topics = 0;
}

void TopicsEngine::send_message(std::string topic_path, std::string text_message)
{
    std::vector<std::string> topics = this->parse_topic_path(topic_path);

    TreeItem* supertopic = find_topic(topics[0], root_topics);
    if (supertopic != nullptr)
    {
        QVector<QVariant> data;
        topics.erase(topics.begin());

        while (topics.size())
        {
            auto subtopic = find_topic1(topics[0], supertopic->getChildren());
            if (subtopic != nullptr)
            {
                topics.erase(topics.begin());
                supertopic = subtopic;
                continue;
            } else {
                create_hierarchy(*supertopic, topics, false, text_message);
                break;
            }
        }
    } else
    {
        create_hierarchy(*this->model.getRoot(), topics, true, text_message);
    }
    std::cout << "Message was added" << std::endl;
    model.layoutChanged();
}

//creates hierarchy of new topics that didn't exist before
void TopicsEngine::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root_topic, std::string text_message)
{
    TreeItem* supertop = &supertopic;
    for (std::string topic : topics)
    {
        if (topic == topics.back())
        {
            supertop = &add_topic(*supertop, topic, {QString::fromStdString(text_message)}); //TODO data
        } else {
            supertop = &add_topic(*supertop, topic, {});
        }
        if (new_root_topic) {
            this->root_topics.push_back(supertop);
            new_root_topic = false;
        }
    }

}


//adds topic to the model and returns pointer to the item of this topic
TreeItem& TopicsEngine::add_topic(TreeItem& supertopic, std::string topic_name, QVariant data = {})
{
    auto child = new TreeItem({QString::fromStdString(topic_name), data}, &supertopic);
    supertopic.appendChild(child);

    return *child;
}

/**
 * @brief TopicsEngine::parse_topic_path
 * @param path
 * @return vector of topic names
 */
std::vector<std::string> TopicsEngine::parse_topic_path(std::string path)
{
    const char* delimeter = "/";
    std::vector<std::string> topics;

    char *token = std::strtok(const_cast<char*>(path.c_str()), delimeter);

    while (token != nullptr)
    {
            topics.push_back(std::string(token));
            token = strtok(nullptr, delimeter);
    }

    return topics;
}

/**
 * @brief TopicsEngine::find_topic checks if the given vector of topics contain a topic with the given name
 * @param name
 * @param topics
 * @return
 */
TreeItem* TopicsEngine::find_topic(std::string name, std::vector<TreeItem*>& topics)
{
    for (auto t : topics)
    {
        if (t->data(0).toString() == QString::fromStdString(name))
        {
            return t;
        }
    }
    return nullptr;
}
//template or overloading???
TreeItem* TopicsEngine::find_topic1(std::string name, const QVector<TreeItem*>& topics)
{
    for (auto t : topics)
    {
        if (t->data(0).toString() == QString::fromStdString(name))
        {
            return t;
        }
    }
    return nullptr;
}


