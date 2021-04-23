#include "maincontroller.h"
#include <iostream>

MainController::MainController(TreeModel& m)
    : model(m)
{
    root_topics = {};
}

MainController::~MainController()
{

}

void MainController::message_recieved(std::string topic_path, QVariant& data, FileType type)
{
    std::vector<std::string> topics = this->parse_topic_path(topic_path);
    TreeItem* supertopic = find_topic(topics[0], root_topics);

    //the first topic of the topic path was used before
    if (supertopic != nullptr)
    {
        //add message to existing first level topic
        if (topics.size() == 1)
        {
            auto t = find_topic(topics[0], root_topics);
            t->addMessage(data.toString());
            model.layoutChanged();
            return;
        }
        topics.erase(topics.begin());

        while (topics.size())
        {
            auto subtopic = find_topic(topics[0], supertopic->getSubtopics());
            //if subtopic was already used, eliminate duplication
            if (subtopic != nullptr)
            {
                if (topics.size() == 1)
                {
                    subtopic->addMessage(data.toString());
                }
                topics.erase(topics.begin());
                supertopic = subtopic;
                continue;
            } else {
                create_hierarchy(*supertopic, topics, false, data);
                break;
            }
        }
    } else
    {
        create_hierarchy(this->model.getRoot(), topics, true, data);
    }

    model.layoutChanged();
}

//creates hierarchy of new topics that didn't exist before
void MainController::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root_topic, QVariant& data)
{
    TreeItem* supertop = &supertopic;
    for (std::string& topic : topics)
    {
        if (topic == topics.back())
        {
            supertop = &add_child(*supertop, topic, {}); //TODO different data
            supertop->addMessage(data.toString());

        } else {
            supertop = &add_child(*supertop, topic, {});
        }
        if (new_root_topic) {
            this->root_topics.push_back(supertop);

            new_root_topic = false;
        }
    }

}

//adds topic to the model and returns pointer to the item of this topic
TreeItem& MainController::add_child(TreeItem& supertopic, std::string topic_name, QVariant data = {})
{
    auto child = new TreeItem({QString::fromStdString(topic_name), data}, &supertopic);
    supertopic.appendSubtopic(child);

    return *child;
}

std::vector<std::string> MainController::parse_topic_path(std::string path)
{
    const char delimeter = '/';
    std::string buff{""};
    std::vector<std::string> topics;

    for(auto n:path)
    {
        if(n != delimeter) buff+=n; else
        if(n == delimeter && buff != "") { topics.push_back(buff); buff = "";}
    }
    if(buff != "") topics.push_back(buff);

    return topics;
}

TreeItem* MainController::find_topic(std::string name, const QVector<TreeItem*>& topics)
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


