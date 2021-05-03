
#include "main.h"

int main(int argc, char **argv)
{
    Devices devices;
    Parser parser;
    Options options;
    parse_arguments(argc, argv, options);

    if (parser.parse_file(options.filename, devices))
    {
        return 1;
    }

    Runner runner(devices, options.server_addres, options.device_flags);

    if (runner.start())
    {
        return 1;
    }

    Log::message("Press ENTER to terminate...");
    std::cin.get();
    Log::message("Please wait, terminating...");

    runner.stop();

    return 0;
}


