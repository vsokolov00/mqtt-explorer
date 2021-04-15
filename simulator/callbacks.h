
#pragma once

#include "mqtt/async_client.h"

class ListnerCallback
{
    public:
		static void on_success_cb(void *object, const mqtt::token& token);
		static void on_failure_cb(void *object, const mqtt::token& token);

    private:
        void on_success(const mqtt::token& token);
        void on_failure(const mqtt::token& token);
};
