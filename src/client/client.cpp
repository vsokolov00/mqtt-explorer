
/**
 * @file        client.cpp                                      
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       API encapsulating the paho mqtt client used by other parts of the application.
 **/

#include "client.h"

const ParsingLevel Client::BINARY = static_cast<ParsingLevel>(FileType::BINARY);
const ParsingLevel Client::STRING = static_cast<ParsingLevel>(FileType::STRING_UTF8);
const ParsingLevel Client::JSON = static_cast<ParsingLevel>(FileType::JSON);
const ParsingLevel Client::JPG = static_cast<ParsingLevel>(FileType::JPG);
const ParsingLevel Client::PNG = static_cast<ParsingLevel>(FileType::PNG);
const ParsingLevel Client::ALL_IMAGES = static_cast<ParsingLevel>(FileType::ALL_IMAGES);
const ParsingLevel Client::AS_BINARY = static_cast<ParsingLevel>(FileType::AS_BINARY);

void Client::add_parsing_level(ParsingLevel &current_levels, FileType file_type)
{
    current_levels |= static_cast<ParsingLevel>(file_type);
}

void Client::remove_parsing_level(ParsingLevel &current_levels, FileType file_type)
{
    current_levels &= ~static_cast<ParsingLevel>(file_type);
}

void Client::dummy_cb(void *object, const mqtt::token& token)
{
    (void)object;
    (void)token;
}

Client::Client(const std::string server_address, const std::string &id, FileType single_file_type,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb)
       : _client(server_address, id),
         _connection_object(connection_object), _connection_success_cb(connected_cb), _connection_lost_cb(connection_lost_cb),
         _connect_listener(connection_object, dummy_cb, connection_failure_cb), 
         _disconect_listener(connection_object, disconnect_success_cb, disconnect_failure_cb),
         _message_object(message_object), _message_arrived_cb(message_arrived_cb), _delivery_complete_cb(delivery_completed_cb),
         _publish_listener(message_object, publish_success_cb, publish_failure_cb), 
         _subscribe_listener(subscription_object, subscribe_success_cb, subscribe_failure_cb),
         _unsubscribe_listener(subscription_object, unsubscribe_success_cb, unsubscribe_failure_cb) 
{
    _level = static_cast<ParsingLevel>(single_file_type);
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

Client::Client(const std::string server_address, const std::string &id, ParsingLevel level,
               void *connection_object, OnConnectionSuccessCB connected_cb, OnConnectionFailureCB connection_failure_cb,
               OnConnectionLostCB connection_lost_cb, OnDisconectSucessCB disconnect_success_cb, 
               OnDisconectFailureCB disconnect_failure_cb, void *message_object, OnMessageArrivedCB message_arrived_cb, 
               OnDeliveryCompleteCB delivery_completed_cb, OnPublishSucessCB publish_success_cb, OnPublishFailureCB publish_failure_cb,
               void *subscription_object, OnSubscribeSucessCB subscribe_success_cb, OnSubscribeFailureCB subscribe_failure_cb,
               OnUnsubscribeSucessCB unsubscribe_success_cb, OnUnsubscribeFailureCB unsubscribe_failure_cb)
       : _client(server_address, id), _level(level),
         _connection_object(connection_object), _connection_success_cb(connected_cb), _connection_lost_cb(connection_lost_cb),
         _connect_listener(connection_object, dummy_cb, connection_failure_cb), 
         _disconect_listener(connection_object, disconnect_success_cb, disconnect_failure_cb),
         _message_object(message_object), _message_arrived_cb(message_arrived_cb), _delivery_complete_cb(delivery_completed_cb),
         _publish_listener(message_object, publish_success_cb, publish_failure_cb), 
         _subscribe_listener(subscription_object, subscribe_success_cb, subscribe_failure_cb),
         _unsubscribe_listener(subscription_object, unsubscribe_success_cb, unsubscribe_failure_cb) 
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

Client::~Client()
{
    delete _reader;
    delete _muttex;
}

void Client::connected(const std::string &cause)
{   
    _connection_success_cb(_connection_object, cause);
}

void Client::connection_lost(const std::string &cause)
{
    _connection_lost_cb(_connection_object, cause);
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

                    if (_level & AS_BINARY)
                    {
                        message_data.binary.data = payload.c_str();
                        message_data.binary.size = payload.size();
                    }
                    else
                    {
                        message_data.json = &root;
                    }
                    _message_arrived_cb(_message_object, topic, message_data, FileType::JSON);
                    return;
                }
                _muttex->unlock();
            }
            
            if (_level & STRING)
            {
                if (_level & AS_BINARY)
                {
                    message_data.binary.data = payload.c_str();
                    message_data.binary.size = payload.size();
                }
                else
                {
                    message_data.string.data = payload.c_str();
                    message_data.string.size = payload.size();
                }
                _message_arrived_cb(_message_object, topic, message_data, FileType::STRING_UTF8);
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
        _message_arrived_cb(_message_object, topic, message_data, FileType::JPG);
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
        _message_arrived_cb(_message_object, topic, message_data, FileType::PNG);
        return;
    }

    if (_level & BINARY)
    {
        message_data.binary.data = payload.c_str();
        message_data.binary.size = payload.size();
        _message_arrived_cb(_message_object, topic, message_data, FileType::BINARY);
        return;
    }
}

void Client::delivery_complete(mqtt::delivery_token_ptr token)
{
    _delivery_complete_cb(_message_object, token);
}

bool Client::connect(const mqtt::connect_options &connect_options)
{
    try
    {
        _client.connect(connect_options, nullptr, _connect_listener);
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
        _client.disconnect(nullptr, _disconect_listener)->wait();
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "Disconnect failed: " << e.what() << std::endl;
        return true;
    }

    return false;
}

void Client::subscribe(const std::string topic, const int QOS)
{
    try
    {
        _client.subscribe(topic, QOS, nullptr, _subscribe_listener);
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Client::unsubscribe(const std::string topic)
{
    try
    {
        _client.unsubscribe(topic, nullptr, _unsubscribe_listener);
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int Client::publish(const std::string topic, const std::string message)
{
    return _client.publish(mqtt::make_message(topic, message), nullptr, _publish_listener)->get_message_id();
}
