
#include "reciever.h"

Reciever::Reciever(const std::string &server_address, const std::string &id) 
         : _connection_listener(this, dummy_cb, on_connection_failure_cb),
           _subscribe_listener(this, on_subscribe_success_cb, on_subscribe_failure_cb),
           _dummy_listener(this, dummy_cb, dummy_cb),
           _listeners(_connection_listener, _subscribe_listener, _dummy_listener, _dummy_listener, _dummy_listener),
           _callbacks(this, on_connected_cb, on_message_arrived_cb, on_connection_lost_cb, on_delivery_complete_dummy_cb),
           _client(server_address, id, _listeners, _callbacks) 
{
    _mutex = new std::mutex();
}

Reciever::~Reciever()
{
    delete _mutex;
}

void Reciever::on_connected_cb(void *object, const std::string &cause)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_connected(cause);
}

void Reciever::on_message_arrived_cb(void *object, mqtt::const_message_ptr message)
{
    Reciever *reciever = static_cast<Reciever *>(object);
    reciever->on_message_arrived(message);
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

void Reciever::on_message_arrived(mqtt::const_message_ptr message)
{
    Message parsed_message;
    if (_parser.parse_message(message, parsed_message))
    {
        return;
    }

    try
    {
        _map.at(parsed_message.topic + parsed_message.id)->on_message_arrived(parsed_message.state, _client, *_mutex);
    }
    catch(const std::out_of_range& e)
    {
        Log::warning("Device with id '" + parsed_message.id + "' does not exist on topic '" + parsed_message.topic + "'.");
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
    if (Log::verbose)
    {
        std::cerr << "LOG: Reciever subscribed successfuly to topic: " << token.get_topics() << std::endl;
    }
}

void Reciever::on_subscribe_failure(const mqtt::token &token)
{
    std::cerr << "WARNING: Reciever could not subscribe to topic: " << token.get_topics() << std::endl;
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
