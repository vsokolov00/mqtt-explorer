
#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>

#include "mqtt/async_client.h"
#include "parser.h"
#include "base_device.h"
#include "client.h"

using OnConnectedCallback = void(*)(void *, const std::string&);
using OnMessageArrivedCallback = void(*)(void *, mqtt::const_message_ptr);
using OnConnectionLostCallback = void(*)(void *, const std::string&);
using OnDeliveryCompleteCallback = void(*)(void *, mqtt::delivery_token_ptr);

class Reciever
{
    public:
        static void on_connected_cb(void *object, const std::string &cause);
        static void on_message_arrived_cb(void *object, mqtt::const_message_ptr message);
        static void on_connection_lost_cb(void *object, const std::string &cause);
        static void on_delivery_complete_dummy_cb(void *object, mqtt::delivery_token_ptr token);
        static void dummy_cb(void *object, const mqtt::token &token);
        static void on_connection_failure_cb(void *object, const mqtt::token &token);
        static void on_subscribe_success_cb(void *object, const mqtt::token &token);
        static void on_subscribe_failure_cb(void *object, const mqtt::token &token);
    
    private:
        std::unordered_map<std::string, RecievingDevice *> _map;
        Parser _parser;
        std::vector<std::string> _topics;
        Listener _connection_listener;
        Listener _subscribe_listener;
        Listener _dummy_listener;
        Listeners _listeners;
        Callbacks _callbacks;
        Client _client;
        std::mutex *_mutex;

        void on_connected(const std::string &cause);
        void on_message_arrived(mqtt::const_message_ptr message);
        void on_connection_lost(const std::string &cause);

        void on_connection_failure(const mqtt::token &token);
        void on_subscribe_success(const mqtt::token &token);
        void on_subscribe_failure(const mqtt::token &token);

    public:
        Reciever(const std::string &server_address, const std::string &id);
        Reciever(const Reciever&) = delete;
        ~Reciever();

        void register_lights(std::vector<Light> &lights);
        void register_relays(std::vector<Relay> &relays);
        void register_valves(std::vector<Valve> &valves);
        void register_thermostats(std::vector<Thermostat> &thermostats);

        bool start_recieving(const mqtt::connect_options &connect_options);
        bool stop_recieving();
};
