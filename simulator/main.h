
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

typedef struct {
    bool condition;
    std::mutex mutex;
    std::condition_variable cond_var;
} thred_control_t;

