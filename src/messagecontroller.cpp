#include "messagecontroller.h"
#include <iostream>

MessageController::MessageController(MainWindow *main_window) : _main_window(main_window) { }

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
    std::string string_message;
    QByteArray binary_message;

    switch (type)
    {
        case FileType::STRING_UTF8:
            string_message = std::string(message.string.data, message.string.size);
            _main_window->get_message_displayer()->display_string(topic, string_message);
            break;

        case FileType::JSON:
            _main_window->get_message_displayer()->display_json(topic, string_message);
            break;

        case FileType::GIF:
        case FileType::JPG:
        case FileType::PNG:
            binary_message = QByteArray(message.binary.data, message.binary.size);
            _main_window->get_message_displayer()->display_image(topic, binary_message);
            break;

        case FileType::BINARY:
            binary_message = QByteArray(message.binary.data, message.binary.size);
            _main_window->get_message_displayer()->display_image(topic, binary_message);
            break;
        
        default:
            break;
    }
}

void MessageController::on_publish_success(const mqtt::token &token)
{
    _main_window->get_message_displayer()->publish_success(token.get_message_id());
    Log::message("Successful message publish: ");
}

void MessageController::on_publish_failure(const mqtt::token &token)
{
    (void)token;

    _main_window->get_message_displayer()->publish_failure(token.get_message_id());
    Log::message("Message publish failed: ");
}

void MessageController::on_delivery_complete(mqtt::delivery_token_ptr token)
{
    if (token.get() == nullptr)
    {
        return;
    }
    
    _main_window->get_message_displayer()->delivery_complete(token.get()->get_message_id());
}

void parse_json_message(Json::Value *root, std::string &parsed_string)
{
    (void)root;
    parsed_string = "";
    //TODO for me...
}
