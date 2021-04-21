
#pragma once

#include "listener.h"
#include "callback.h"
#include "json/json-forwards.h"
#include "json/json.h"

#include <string>
#include <thread>

class Client : public virtual mqtt::callback
{
    private:
        static ParsingLevel BINARY;
        static ParsingLevel STRING;
        static ParsingLevel JSON;
        static ParsingLevel JPG;
        static ParsingLevel PNG;
        static ParsingLevel GIF;
        static ParsingLevel ALL_IMAGES;

    public:
        static void add_parsing_level(ParsingLevel &current_levels, FileType file_type);
        static void remove_parsing_level(ParsingLevel &current_levels, FileType file_type);

    private:
        void connected(const std::string &cause) override;
        void connection_lost(const std::string &cause) override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;

        mqtt::async_client _client;
        Listeners _listeners;
        Callbacks _callbacks;

        ParsingLevel _level;
        Json::CharReader *_reader;
        std::mutex *_muttex;

    public:
        Client(const std::string server_address, const std::string &id, Listeners &listeners, 
               Callbacks &callbacks, ParsingLevel level);
        Client(const std::string server_address, const std::string &id, 
               Listeners &listeners, Callbacks &callbacks, FileType single_file_type);
        Client(const Client&) = delete;
        ~Client();

        bool connect(const mqtt::connect_options &connect_options);
        bool disconnect();
        void subscribe(const std::string topic, const int QOS);
        void unsubscribe(const std::string topic);
        void publish(const std::string topic, const std::string message);
};
