
#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>

#include "mqtt/async_client.h"
#include "parser.h"
#include "base_device.h"
#include "client.h"
#include "options.h"
#include "log.h"

class Reciever
{
    public:
        static void on_connected_cb(void *object, const std::string &cause);
        static void on_message_arrived_cb(void *object, const std::string &topic, const MessageData &message, FileType type);
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
        void on_message_arrived(const std::string &topic, const Json::Value &root);
        void on_connection_lost(const std::string &cause);

        void on_connection_failure(const mqtt::token &token);
        void on_subscribe_success(const mqtt::token &token);
        void on_subscribe_failure(const mqtt::token &token);

        template<typename T> void register_device(std::vector<T> &device);

    public:
        Reciever(const std::string &server_address, const std::string &id);
        Reciever(const Reciever&) = delete;
        ~Reciever();

        void regiser_devices(Devices &devices, unsigned flags);

        bool start_recieving(const mqtt::connect_options &connect_options);
        bool stop_recieving();
};
