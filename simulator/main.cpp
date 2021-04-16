
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
    Parser parser;
      

    if (parser.parse_file("file.json", devices))
    {
        return 1;
    }

    std::cerr << "Starting devices..." << std::endl;
    Runner runner(devices, "tcp://localhost:1883");

    if (runner.start())
    {
        return 1;
    }

    std::cin.get();
    std::cout << "Please wait, terminating..." << std::endl;

    runner.stop();

    std::cout << "Bye" << std::endl;
    return 0;
}


