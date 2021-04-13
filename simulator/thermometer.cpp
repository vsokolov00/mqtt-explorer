
#include "thermometer.h"

Thermometer::Thermometer(std::string name, std::string location, int max, int min, float average, float deviation, int period)
                : name(name), location(location), max(max), min(min), average(average), deviation(deviation), period(period) {}

void Thermometer::run_thermometer()
{
    while (run)
    {
        std::cout << "name: " << name << ", location: " << location << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(period));
    }
}
