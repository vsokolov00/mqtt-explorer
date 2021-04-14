
#include "thermometer.h"

Thermometer::Thermometer(std::string topic, std::string name, std::string location, int period, float min_temp, float max_temp, 
                         float min_step, float max_step, float temp, std::string unit)
                : Device(topic, name, location, period), min_temp(min_temp), max_temp(max_temp), min_step(min_step), 
                  max_step(max_step), temp(temp), unit(unit) { }

void Thermometer::run_thermometer(mqtt::client &client, const bool &run, std::mutex &mutex, 
                                  std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(min_step * 1000, max_step * 1000), std::default_random_engine());
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine());

    float step;
    bool up_down;
    
    Json::Value root;
    Json::StreamWriter *writer = Json::StreamWriterBuilder().newStreamWriter();
    std::ostringstream stream;
    std::string json_str;

    while (run)
    {
        step = step_generator() / 1000.0f;
        std::cout << "name: " << name << ", step: " << step << std::endl;
        up_down = up_down_generator();

        if (up_down)
        {
            temp = temp + step > max_temp ? max_temp : temp + step;
        }
        else
        {
            temp = temp - step < min_temp ? min_temp : temp - step;
        }
        
        root["value"] = temp;
        root["unit"] = unit;
        writer->write(root, &stream);
        json_str = stream.str();
        message->set_payload(json_str.c_str(), json_str.size());

        std::unique_lock<std::mutex> lock(mutex);
            client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
    }

    delete writer;
}

