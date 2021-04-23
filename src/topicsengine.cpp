#include "topicsengine.h"
#include <iostream>

TopicsEngine::TopicsEngine(TreeModel& m)
    : model(m)
{
    root_topics = {};
    total_topics = 0;
}

/**
 * @brief TopicsEngine::recieve_message recieves topic path and message from running MQTT client and displays it
 * @param topic_path
 * @param text_message
 */
void TopicsEngine::recieve_message(std::string topic_path, QVariant& data)
{
    std::vector<std::string> topics = this->parse_topic_path(topic_path);
    TreeItem* supertopic = find_topic(topics[0], root_topics);

    //the first topic of the topic path was used before
    if (supertopic != nullptr)
    {
        //QVector<QVariant> data;
        topics.erase(topics.begin());

        while (topics.size())
        {
            auto subtopic = find_topic1(topics[0], supertopic->getSubtopics());
            //if subtopic was already used, eliminate duplication
            if (subtopic != nullptr)
            {
                if (topics.size() == 1)
                {
                    subtopic->addMessage(data.toString());
//                    subtopic->m_itemData[1] = QString::fromStdString(text_message);
//                    add_child(*subtopic, "message" + std::to_string(subtopic->getMessageCnt()), QString::fromStdString(text_message));
                }
                topics.erase(topics.begin());
                supertopic = subtopic;
                continue;
            } else {
                create_hierarchy(*supertopic, topics, topic_path, false, data);
                break;
            }
        }
    } else
    {
        create_hierarchy(*this->model.getRoot(), topics, topic_path, true, data);
    }
    std::cout << "Message was added" << std::endl;
    model.layoutChanged();
}

//creates hierarchy of new topics that didn't exist before
void TopicsEngine::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, std::string full_path, bool new_root_topic, QVariant& data)
{
    TreeItem* supertop = &supertopic;
    for (std::string topic : topics)
    {
        if (topic == topics.back())
        {
            supertop = &add_child(*supertop, topic, {}, full_path); //TODO different data
            supertop->addMessage(data.toString());
            //add_child(*supertop, "message" + std::to_string(supertop->getMessageCnt()), QString::fromStdString(text_message));

        } else {
            supertop = &add_child(*supertop, topic, {}, full_path);
        }
        if (new_root_topic) {
            this->root_topics.push_back(supertop);
            new_root_topic = false;
        }
    }

}


//adds topic to the model and returns pointer to the item of this topic
TreeItem& TopicsEngine::add_child(TreeItem& supertopic, std::string topic_name, QVariant data = {}, std::string path = "")
{
    auto child = new TreeItem({QString::fromStdString(topic_name), data}, &supertopic, path);
    supertopic.appendSubtopic(child);

    return *child;
}

/**
 * @brief TopicsEngine::parse_topic_path
 * @param path
 * @return vector of topic names
 */
std::vector<std::string> TopicsEngine::parse_topic_path(std::string path)
{
    std::vector<std::string> topics;
    const char* delimeter = "/";
    char *token = strtok(const_cast<char*>(path.c_str()), delimeter);

    while (token != nullptr)
    {
            topics.push_back(std::string(token));
            token = strtok(nullptr, delimeter);
    }

    return topics;
}

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


