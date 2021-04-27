#include "message_controller.h"
#include <iostream>

MessageController::MessageController(TreeModel *tree_model, MainWidgetModel *main_widget_model) 
                  : _tree_model(tree_model), _main_widget_model(main_widget_model) { }

void MessageController::on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type)
{
    MessageController *message_controller = static_cast<MessageController *>(object);
    message_controller->on_message_arrived(topic, message, type);
}

void MessageController::on_publish_success_cb(void *object, const mqtt::token &token)
{
    MessageController *message_controller = static_cast<MessageController *>(object);
    message_controller->on_publish_success(token);
}

void MessageController::on_publish_failure_cb(void *object, const mqtt::token &token)
{
    MessageController *message_controller = static_cast<MessageController *>(object);
    message_controller->on_publish_failure(token);
}

void MessageController::on_delivery_complete_cb(void *object, mqtt::delivery_token_ptr token)
{
    MessageController *message_controller = static_cast<MessageController *>(object);
    message_controller->on_delivery_complete(token);
}

void MessageController::on_message_arrived(const std::string &topic, const MessageData &message, FileType type)
{
    Log::log("Message arrived on topic: " + topic);
    QVariant variant;
    TreeItem *topic_item = get_topic(topic);

    switch (type)
    {
        case FileType::STRING_UTF8:
            variant = QVariant(QByteArray(message.string.data, message.string.size));
            break;

        case FileType::JSON:
            break;

        case FileType::GIF:
        case FileType::JPG:
        case FileType::PNG:
            variant = QVariant(QByteArray(message.binary.data, message.binary.size));
            break;

        case FileType::BINARY:
            variant = QVariant(QByteArray(message.binary.data, message.binary.size));
            break;
        
        default:
            return;
    }

    topic_item->addMessage(variant, static_cast<int>(type));
    emit _tree_model->layoutChanged();

}

void MessageController::on_publish_success(const mqtt::token &token)
{
    _main_widget_model->publish_success(token.get_message_id());
    Log::log("Message published successfuly.");
}

void MessageController::on_publish_failure(const mqtt::token &token)
{
    (void)token;

    _main_widget_model->publish_failure(token.get_message_id());
    Log::log("Publishing failed.");
}

void MessageController::on_delivery_complete(mqtt::delivery_token_ptr token)
{
    if (token.get() == nullptr)
    {
        return;
    }
    
    _main_widget_model->delivery_complete(token.get()->get_message_id());
}

void MessageController::register_client(Client *client)
{
    _client = client;
}

void MessageController::parse_json_message(Json::Value *root, std::string &parsed_string)
{
    (void)root;
    parsed_string = "";
    //TODO for me...
}

void MessageController::publish(const std::string &topic, const std::string &message)
{
    _client->publish(topic, message);
}

//creates hierarchy of new topics that didn't exist before
TreeItem *MessageController::create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, 
                                              bool new_root_topic)
{
    TreeItem* supertop = &supertopic;
    for (std::string& topic : topics)
    {
        if (topic == topics.back())
        {
            return &add_subtopic(*supertop, topic, {});

        } else {
            supertop = &add_subtopic(*supertop, topic, {});
        }
        if (new_root_topic) {
            this->_root_topics.push_back(supertop);

            new_root_topic = false;
        }
    }

    return supertop;
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

    for(auto n: path)
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

TreeItem *MessageController::get_topic(std::string topic_path)
{
    std::vector<std::string> topics = parse_topic_path(topic_path);
    TreeItem* supertopic = find_topic(topics[0], _root_topics);
    TreeItem* found_topic;

    //the first topic of the topic path was used before
    if (supertopic != nullptr)
    {
        //add message to existing first level topic
        if (topics.size() == 1)
        {
            return find_topic(topics[0], _root_topics);
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
                    found_topic = subtopic;
                }
                topics.erase(topics.begin());
                supertopic = subtopic;
                continue;
            } else {
                return create_hierarchy(*supertopic, topics, false);
                break;
            }
        }
    } else
    {
        return create_hierarchy(_tree_model->getRoot(), topics, true);
    }

    return found_topic;
}
