
/**
 * @file        reciever.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Reciever class
 *              used for recieving MQTT messages.
 **/

#include "reciever.h"

Reciever::Reciever(const std::string &server_address, const std::string &id) 
         : _client(server_address, id, FileType::JSON, this, &Reciever::on_connection_success_cb, &Reciever::on_connection_failure_cb,
           &Reciever::on_connection_lost_cb, &Reciever::dummy_cb, &Reciever::dummy_cb, this, &Reciever::on_message_arrived_cb, 
           &Reciever::on_delivery_complete_dummy_cb, &Reciever::dummy_cb, &Reciever::dummy_cb, this, &Reciever::on_subscribe_success_cb,
           &Reciever::on_subscribe_failure_cb, &Reciever::dummy_cb, &Reciever::dummy_cb) 
{
    _mutex = new std::mutex();
}

Reciever::~Reciever()
{
    delete _mutex;
}

void Reciever::on_connection_success_cb(void *object, const std::string &cause)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_connected(cause);
}

void Reciever::on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type)
{
    (void)type;
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_message_arrived(topic, *message.json);
}

void Reciever::on_connection_lost_cb(void *object, const std::string &cause)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_connection_lost(cause);
}

void Reciever::on_delivery_complete_dummy_cb(void *object, mqtt::delivery_token_ptr token)
{
    //dummy
    (void)object;
    (void)token;
}

void Reciever::dummy_cb(void *object, const mqtt::token &token)
{
    //dummy
    (void)object;
    (void)token;
}

void Reciever::on_connection_failure_cb(void *object, const mqtt::token &token)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_connection_failure(token);
}
void Reciever::on_subscribe_success_cb(void *object, const mqtt::token &token)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_subscribe_success(token);
}
void Reciever::on_subscribe_failure_cb(void *object, const mqtt::token &token)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_subscribe_failure(token);
}

void Reciever::on_connected(const std::string &cause)
{
    Log::log("Reciever connected: " + cause);

    for (auto &topic: _topics)
    {
        Log::log("Reciever is subscribing to topic: " + topic);
        _client.subscribe(topic, 1);
    }
}

void Reciever::on_message_arrived(const std::string &topic, const Json::Value &root)
{
    if (!root["id"] || !root["state"])
    {
        return;
    }

    std::string id = root["id"].asString();
    std::string state = root["state"].asString();
    
    try
    {
        _map.at(topic + id)->on_message_arrived(state, _client, *_mutex);
    }
    catch(const std::out_of_range& e)
    {
        Log::warning("Device with id '" + id + "' does not exist on topic '" + topic + "'.");
    }
}

void Reciever::on_connection_lost(const std::string &cause)
{
    Log::warning("Reciever lost connection: " + cause);
}

template<typename T> void Reciever::register_device(std::vector<T> &devices)
{
    for (auto &device: devices)
    {
        if (std::find(_topics.begin(), _topics.end(), device.recv_topic) == _topics.end())
        {
            _topics.push_back(device.recv_topic);
        }

        _map[device.recv_topic + device.id] = &device;
    }
}

void Reciever::regiser_devices(Devices &devices, unsigned flags)
{
    try
    {
        if (flags & LIGHTS_FLAG)
        {
            register_device<Light>(devices.lights);
        }
        if (flags & LOCKS_FLAG)
        {
            register_device<Lock>(devices.locks);
        }
        if (flags & VALVES_FLAG)
        {
            register_device<Valve>(devices.valves);
        }
        if (flags & THERMOSTAT_FLAG)
        {
            register_device<Thermostat>(devices.thermostats);
        }
        if (flags & RELAYS_FLAG)
        {
            register_device<Relay>(devices.relays);
        }
    }
    catch(const std::bad_alloc &e)
    {
        std::stringstream message;
        message << "Registration of recieving devices failed with '" << e.what() << "' some may still recieve.";
        Log::warning(message.str());
    }
}

void Reciever::on_connection_failure(const mqtt::token &token)
{
    Log::warning("Reciever failed to connect with code: " + token.get_reason_code());
}

void Reciever::on_subscribe_success(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::log("Reciever subscribed successfuly to topic: " + (*topics)[i]);
    }
}

void Reciever::on_subscribe_failure(const mqtt::token &token)
{
    const mqtt::string_collection *topics = token.get_topics().get();
    if (topics == nullptr)
    {
        return;
    }
    for (unsigned i = 0; i < topics->size(); i++)
    {
        Log::warning("Reciever could not subscribe to topic: " + (*topics)[i]);
    }
}

bool Reciever::start_recieving(const mqtt::connect_options &connect_options)
{
    Log::log("Connecting reciever...");
    return _client.connect(connect_options);
}

bool Reciever::stop_recieving()
{
    return _client.disconnect();
}
