
#include "wattmeter.h"

Wattmeter::Wattmeter(std::string topic, std::string name, int period, int min_val, 
                  int max_val, int min_step, int max_step, int value, std::string unit)
          :Device(topic, name, period), _min_val(min_val), _max_val(max_val), _min_step(min_step),
           _max_step(max_step), _value(value), _unit(unit) {}

void Wattmeter::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(_min_step, _max_step), std::default_random_engine());
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine());

    float step;
    bool up_down;
    std::string value_str;

    future.wait_for(std::chrono::seconds(_period));
    while (run)
    {
        step = step_generator();
        std::cout << "name: " << _name << ", step: " << step << std::endl;
        up_down = up_down_generator();

        if (up_down)
        {
            _value = _value + step > _max_val ? _max_val : _value + step;
        }
        else
        {
            _value = _value - step < _min_val ? _min_val : _value - step;
        }

        value_str = _name + ": " + std::to_string(_value) + " " + _unit;
        message->set_payload(value_str.c_str(), value_str.size());
        
        std::unique_lock<std::mutex> lock(mutex);
            client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(_period));
    }
}
