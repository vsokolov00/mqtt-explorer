
#include "thermometer.h"

Thermometer::Thermometer(std::string topic, std::string name, std::string location, float min_temp, float max_temp, 
                         float min_step, float max_step, float temp, int period)
                : topic(topic), name(name), location(location), min_temp(min_temp), max_temp(max_temp), min_step(min_step), 
                  max_step(max_step), temp(temp), period(period) {}

void Thermometer::run_thermometer(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(topic, name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(min_step * 1000, max_step * 1000), std::default_random_engine());
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine());

    float step;
    bool up_down;
    std::string temp_str;

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
        temp_str = std::to_string(temp);
        message->set_payload(temp_str.c_str(), temp_str.size());
        
        std::unique_lock<std::mutex> lock(mutex);
        client.publish(message);
        lock.unlock();

        future.wait_for(std::chrono::seconds(period));
    }
}

ThermometerRunner::ThermometerRunner(std::vector<Thermometer> &thermometers, const std::string &server_address)
                    : _thermometers(thermometers), _client(server_address, "simulator_thermometers_client_ID") 
{
    mqtt::connect_options connection_opts;
    connection_opts.set_keep_alive_interval(60);
    connection_opts.set_clean_session(true);

    try
    {
        _client.connect(connection_opts);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        not_runable = true;
    }
}

void ThermometerRunner::run_thermometers()
{
    _run = true;

    _threads.reserve(_thermometers.size());
    _promises.reserve(_thermometers.size());

    for (unsigned i = 0; i < _thermometers.size(); i++)
    {
        _promises.push_back(std::promise<void>());
        _threads.push_back(std::thread(&Thermometer::run_thermometer, _thermometers[i], 
                                      std::ref(_client), std::ref(_run), std::ref(_mutex), _promises[i].get_future()));
    }
}

void ThermometerRunner::stop_thermometers()
{
    _run = false;

    for (auto &promise: _promises)
    {
        promise.set_value();
    }

    for (auto &thread: _threads)
    {
        thread.join();
    }
}

