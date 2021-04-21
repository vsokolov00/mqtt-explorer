
#include "client.h"

ParsingLevel Client::BINARY = static_cast<unsigned short>(FileType::BINARY);
ParsingLevel Client::STRING = static_cast<unsigned short>(FileType::STRING_UTF8);
ParsingLevel Client::JSON = static_cast<unsigned short>(FileType::JSON);
ParsingLevel Client::JPG = static_cast<unsigned short>(FileType::JPG);
ParsingLevel Client::PNG = static_cast<unsigned short>(FileType::PNG);
ParsingLevel Client::GIF = static_cast<unsigned short>(FileType::GIF);
ParsingLevel Client::ALL_IMAGES = static_cast<unsigned short>(FileType::ALL_IMAGES);

void Client::add_parsing_level(ParsingLevel &current_levels, FileType file_type)
{
    current_levels |= static_cast<unsigned short>(file_type);
}

void Client::remove_parsing_level(ParsingLevel &current_levels, FileType file_type)
{
    current_levels &= ~static_cast<unsigned short>(file_type);
}

Client::Client(const std::string server_address, const std::string &id, Listeners &listeners, 
               Callbacks &callbacks, ParsingLevel level)
       : _client(server_address, id), _listeners(listeners), _callbacks(callbacks), _level(level)
{
    _client.set_callback(*this);

    try
    {
        _muttex = new std::mutex();        
    }
    catch(const std::bad_alloc &e)
    {
        std::cerr << "ERROR: memory allocation failed." << std::endl;
        exit(1);
    }
    
    _reader = Json::CharReaderBuilder().newCharReader();
    if (_reader == nullptr)
    {
        delete _muttex;
        std::cerr << "ERROR: memory allocation failed." << std::endl;
        exit(1);
    }
}

Client::Client(const std::string server_address, const std::string &id, 
               Listeners &listeners, Callbacks &callbacks, FileType single_file_type)
       : _client(server_address, id), _listeners(listeners), _callbacks(callbacks)
{
    _level = static_cast<ParsingLevel>(single_file_type);
    _client.set_callback(*this);

    try
    {
        _muttex = new std::mutex();
        std::cerr << _muttex << std::endl;
    }
    catch(const std::bad_alloc &e)
    {
        std::cerr << "ERROR: memory allocation failed." << std::endl;
        exit(1);
    }
    
    _reader = Json::CharReaderBuilder().newCharReader();
    if (_reader == nullptr)
    {
        delete _muttex;
        std::cerr << "ERROR: memory allocation failed." << std::endl;
        exit(1);
    }
}

Client::~Client()
{
    delete _reader;
    delete _muttex;
}

void Client::connected(const std::string &cause)
{   
    _callbacks.on_connected(_callbacks.on_connected_object, cause);
}

void Client::connection_lost(const std::string &cause)
{
    _callbacks.on_connection_lost(_callbacks.on_connection_lost_object, cause);
}

void Client::message_arrived(mqtt::const_message_ptr msg)
{
    bool printable{true};
    MessageData message_data;
    const mqtt::message *message = msg.get();
    if (message == nullptr)
    {
        return;
    }

    const std::string topic = message->get_topic();
    const mqtt::binary payload = message->get_payload();

    if (_level & (STRING | JSON))
    {
        unsigned count{0};
        for (unsigned char c: payload)
        {
            if (count == 0)
            {
                if (c >> 3 == 0b11110)
                {
                    count = 3;
                }
                else if (c >> 4 == 0b1110)
                {
                    count = 2;
                }
                else if (c >> 5 == 0b110)
                {
                    count = 1;
                }
                else if (c >> 7)
                {
                    printable = false;
                    break;
                }
            }
            else
            {
                if (c >> 6 == 0b10)
                {
                    count--;
                }
                else
                {
                    printable = false;
                    break;
                }
            }
        }
        printable = !printable ? false : count == 0;

        if (printable)
        {
            if (_level & JSON)
            {
                Json::Value root;

                _muttex->lock();
                if (_reader->parse(payload.c_str(), payload.c_str() + payload.size(), &root, nullptr))
                {
                    _muttex->unlock();
                    message_data.json = &root;
                    _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::JSON);
                    return;
                }
                _muttex->unlock();
            }
            else if (_level & STRING)
            {
                message_data.string.data = payload.c_str();
                message_data.string.size = payload.size();
                _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::STRING_UTF8);
                return;
            }
        }
    }

    if ((_level & JPG) && payload.size() >= 4 && static_cast<unsigned char>(payload[0]) == 0xFF
                                              && static_cast<unsigned char>(payload[1]) == 0xD8
                                              && static_cast<unsigned char>(payload[2]) == 0xFF
                                              && (static_cast<unsigned char>(payload[3]) == 0xDB 
                                              || static_cast<unsigned char>(payload[3]) == 0xE0 
                                              || static_cast<unsigned char>(payload[3]) == 0xEE 
                                              || static_cast<unsigned char>(payload[3]) == 0xE1))
    {
        message_data.binary.data = payload.c_str();
        message_data.binary.size = payload.size();
        _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::JPG);
        return;
    }

    if ((_level & PNG) && payload.size() >= 8 && static_cast<unsigned char>(payload[0]) == 0x89 
                                              && static_cast<unsigned char>(payload[1]) == 0x50
                                              && static_cast<unsigned char>(payload[2]) == 0x4E 
                                              && static_cast<unsigned char>(payload[3]) == 0x47
                                              && static_cast<unsigned char>(payload[4]) == 0x0D 
                                              && static_cast<unsigned char>(payload[5]) == 0x0A
                                              && static_cast<unsigned char>(payload[6]) == 0x1A 
                                              && static_cast<unsigned char>(payload[7]) == 0x0A)
    {
        message_data.binary.data = payload.c_str();
        message_data.binary.size = payload.size();
        _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::PNG);
        return;
    }

    if ((_level & GIF) && payload.size() >= 6 && static_cast<unsigned char>(payload[0]) == 0x47 
                                              && static_cast<unsigned char>(payload[1]) == 0x49
                                              && static_cast<unsigned char>(payload[2]) == 0x46 
                                              && static_cast<unsigned char>(payload[3]) == 0x38
                                              && (static_cast<unsigned char>(payload[4]) == 0x37 
                                              || static_cast<unsigned char>(payload[4]) == 0x39) 
                                              && static_cast<unsigned char>(payload[5]) == 0x61)
    {
        message_data.binary.data = payload.c_str();
        message_data.binary.size = payload.size();
        _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::GIF);
        return;
    }

    if (_level & BINARY)
    {
        message_data.binary.data = payload.c_str();
        message_data.binary.size = payload.size();
        _callbacks.on_message_arrived(_callbacks.on_message_arrived_object, topic, message_data, FileType::BINARY);
        return;
    }
}

void Client::delivery_complete(mqtt::delivery_token_ptr token)
{
    _callbacks.on_delivery_complete(_callbacks.on_delivery_complete_object, token);
}

bool Client::connect(const mqtt::connect_options &connect_options)
{
    try
    {
        _client.connect(connect_options, nullptr, _listeners.connect_listener);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "ERROR: Connection was not established: " << exc.what() << std::endl;
        return true;
    }
    
    return false;
}

bool Client::disconnect()
{
    try
    {
        _client.disconnect(nullptr, _listeners.disconect_listener)->wait();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Disconnect failed: " << exc.what() << std::endl;
        return true;
    }

    return false;
}

void Client::subscribe(const std::string topic, const int QOS)
{
    _client.subscribe(topic, QOS, nullptr, _listeners.subscribe_listener);
}

void Client::unsubscribe(const std::string topic)
{
    _client.unsubscribe(topic, nullptr, _listeners.unsubscribe_listener);
}

void Client::publish(const std::string topic, const std::string message)
{
    _client.publish(mqtt::make_message(topic, message), nullptr, _listeners.publish_listener);
}
