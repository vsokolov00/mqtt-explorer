
#include "wattmeter.h"

Wattmeter::Wattmeter(std::string topic, std::string name, std::string location, int period, int min_val, 
                  int max_val, int min_step, int max_step, int value, std::string unit)
          :Device(topic, name, location, period), min_val(min_val), max_val(max_val), min_step(min_step),
           max_step(max_step), value(value), unit(unit) {}

void Wattmeter::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(min_step, max_step), std::default_random_engine());
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine());

    float step;
    bool up_down;
    std::string value_str;

    while (run)
    {
        step = step_generator();
        std::cout << "name: " << name << ", step: " << step << std::endl;
        up_down = up_down_generator();

        if (up_down)
        {
            value = value + step > max_val ? max_val : value + step;
        }
        else
        {
            value = value - step < min_val ? min_val : value - step;
        }

        value_str = name + " " + std::to_string(value);
        message->set_payload(value_str.c_str(), value_str.size());
        
        std::unique_lock<std::mutex> lock(mutex);
            client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
    }
}
