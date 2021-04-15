
#include "move_sensors.h"

MoveSensors::MoveSensors(std::string topic, std::string name, int min_period, 
                         int max_period, int horizontal_FOV, int vertical_FOV)
            : Device(topic, name, min_period), max_period(max_period), horizontal_FOV(horizontal_FOV), 
              vertical_FOV(vertical_FOV) {}

void MoveSensors::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    auto period_generator = std::bind(std::uniform_int_distribution<int>(period, max_period), std::default_random_engine());
    auto horizontal_generator = std::bind(std::uniform_int_distribution<int>(0, horizontal_FOV), std::default_random_engine());
    auto vertical_generator = std::bind(std::uniform_int_distribution<int>(0, vertical_FOV), std::default_random_engine());

    std::string sensor_str;

    while (run)
    {
        std::cout << "name: " << name << std::endl;

        message->set_payload(sensor_str.c_str(), sensor_str.size());
        
        std::unique_lock<std::mutex> lock(mutex);
            client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
    }
}
