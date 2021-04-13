
#include "thermometer.h"

Thermometer::Thermometer(std::string topic, std::string name, std::string location, int max, int min, 
                         float average, float deviation, int period)
                : topic(topic), name(name), location(location), max(max), min(min), average(average), 
                  deviation(deviation), period(period) {}

void Thermometer::run_thermometer(mqtt::client &client, thred_control_t &control, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    int x;
    std::string temp;
    while (control.condition)
    {
        x = rand() % 50;
        temp = std::to_string(x);
        message->set_payload(temp.c_str(), temp.size());

        std::unique_lock<std::mutex> lock(control.mutex);
        client.publish(message);

        std::cout << "name: " << name << ", location: " << location << std::endl;
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
        //std::this_thread::sleep_for(std::chrono::seconds(period));
    }
}
