
#include "hygrometer.h"

Hygrometer::Hygrometer(std::string topic, std::string name, std::string location, int period, 
                       float min_step, float max_step, float humidity)
            : Device(topic, name, location, period), min_step(min_step), max_step(max_step) 
{
    (*this).humidity = humidity >= 0.0f && humidity <= 100.f ? humidity : 50.0f;
}


void Hygrometer::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(min_step * 1000, max_step * 1000), std::default_random_engine());
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine());

    float step;
    bool up_down;
    std::string humidity_template_str{"location: " + location + ", device name: " + name + ", humidity: "};
    std::string humidity_str;

    while (run)
    {
        step = step_generator() / 1000.0f;
        std::cout << "name: " << name << ", step: " << step << std::endl;
        up_down = up_down_generator();

        if (up_down)
        {
            humidity = humidity + step > 100.f ? 100.0f : humidity + step;
        }
        else
        {
            humidity = humidity - step < 0.0f ? 0.0f : humidity - step;
        }

        humidity_str = humidity_template_str + std::to_string(humidity);
        humidity_str.pop_back();
        humidity_str.pop_back();
        humidity_str.pop_back();
        humidity_str += "%";
        message->set_payload(humidity_str.c_str(), humidity_str.size());
        
        std::unique_lock<std::mutex> lock(mutex);
        client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
    }
}
