#include "messagecontroller.h"
#include <iostream>

MessageController::MessageController(TreeModel& m)
    : model(m)
{
    root_topics = {};
}

MessageController::~MessageController()
{

}

void MessageController::message_recieved(std::string topic_path, QVariant& data, FileType type)
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
            t->addMessage(data.toString(), (int)type);
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
                    subtopic->addMessage(data.toString(), (int)type);
                }
                topics.erase(topics.begin());
                supertopic = subtopic;
                continue;
            } else {
                create_hierarchy(*supertopic, topics, false, data, type);
                break;
            }
        }
    } else
    {
        create_hierarchy(this->model.getRoot(), topics, true, data, type);
    }

    model.layoutChanged();
}

//creates hierarchy of new topics that didn't exist before
void MessageController::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, bool new_root_topic, QVariant& data, FileType type)
{
    TreeItem* supertop = &supertopic;
    for (std::string& topic : topics)
    {
        if (topic == topics.back())
        {
            supertop = &add_subtopic(*supertop, topic, {});
            supertop->addMessage(data.toString(), (int)type);

        } else {
            supertop = &add_subtopic(*supertop, topic, {});
        }
        if (new_root_topic) {
            this->root_topics.push_back(supertop);

            new_root_topic = false;
        }
    }

}

//adds topic to the model and returns pointer to the item of this topic
TreeItem& MessageController::add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data = {})
{
    auto child = new TreeItem({QString::fromStdString(topic_name), data}, &supertopic);
    supertopic.appendSubtopic(child);

    return *child;
}

std::vector<std::string> MessageController::parse_topic_path(std::string path)
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

TreeItem* MessageController::find_topic(std::string name, const QVector<TreeItem*>& topics)
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

bool MessageController::publish_msg(std::string topic, QVariant msg)
{
    //publish&wait for feedback
    if (this->file_chosen)
    {
        //send chosen file
        this->message_recieved(topic, this->get_message(), this->get_message_type());
    }
    else
    {
        this->message_recieved(topic, msg, FileType::STRING_UTF8);
    }

    sleep(1);
    return true;
}

void MessageController::set_message(QVariant content, FileType type)
{
    this->file_to_publish = content;
    this->file_type = type;
}

QVariant& MessageController::get_message()
{
    return file_to_publish;
}

FileType MessageController::get_message_type()
{
    return file_type;
}

void MessageController::set_file_chosen()
{
    this->file_chosen = true;
}
void MessageController::set_file_not_chosen()
{
    this->file_chosen = false;
}

