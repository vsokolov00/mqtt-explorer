
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

typedef struct {
    bool condition;
    std::mutex mutex;
    std::condition_variable cond_var;
} thred_control_t;

