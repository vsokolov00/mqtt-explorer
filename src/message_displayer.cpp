
#include "message_displayer.h"

MessageDisplayer::MessageDisplayer(TreeModel *tree_model) : _tree_model(tree_model) {}

//creates hierarchy of new topics that didn't exist before
void MessageDisplayer::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, 
                                        bool new_root_topic, QVariant& data, FileType type)
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
            this->_topics.push_back(supertop);

            new_root_topic = false;
        }
    }

}

//adds topic to the model and returns pointer to the item of this topic
TreeItem& MessageDisplayer::add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data = {})
{
    auto child = new TreeItem({QString::fromStdString(topic_name), data}, &supertopic);
    supertopic.appendSubtopic(child);

    return *child;
}

std::vector<std::string> MessageDisplayer::parse_topic_path(std::string path)
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

TreeItem* MessageDisplayer::find_topic(std::string name, const QVector<TreeItem*>& topics)
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

void MessageDisplayer::display_string(const std::string &topic, const std::string &string_message)
{
    (void)topic;
    (void)string_message;
    //TODO
}

void MessageDisplayer::display_json(const std::string &topic, const std::string &json_file)
{
    (void)topic;
    (void)json_file;
    //TODO
}

void MessageDisplayer::display_image(const std::string &topic, const QByteArray &image)
{
    (void)topic;
    (void)image;
    //TODO
}

void MessageDisplayer::display_binary(const std::string &topic, const QByteArray &binary_file)
{
    (void)topic;
    (void)binary_file;
    //TODO
}

void MessageDisplayer::publish_success(int message_id)
{
    (void)message_id;
    // TODO register the ID and wait for delivery complete
}

void MessageDisplayer::publish_failure(int message_id)
{
    (void)message_id;
    //TODO inform the user
}

void MessageDisplayer::delivery_complete(int message_id)
{
    (void)message_id;
    //TODO find the ID and mark the message as delivered
}

//TODO recycle this
/*void MessageController::message_recieved(std::string topic_path, QVariant& data, FileType type)
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
            //model.layoutChanged();
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
*/
