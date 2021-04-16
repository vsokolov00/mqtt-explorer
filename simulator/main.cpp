
#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"
#include "parser.h"
#include "thermometer.h"
#include "runner.h"
#include "client.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void test_func(void *ptr, const mqtt::token &token)
{
    (void)ptr;
    (void)token;
}

int main()
{
    Listener listener(nullptr, test_func, test_func);

    Devices devices;
    Parser parser("file.json");
      

    if (parser.parse_file(devices))
    {
        return 1;
    }

    Runner runner(devices, "tcp://localhost:1883");

    if (runner.not_runable)
        return 1;

    runner.run_threads();

    std::cin.get();
    std::cout << "Please wait, terminating..." << std::endl;

    runner.stop_threads();

    std::cout << "Bye" << std::endl;
    return 0;
}


