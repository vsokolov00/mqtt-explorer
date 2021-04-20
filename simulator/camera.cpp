
#include "camera.h"

Camera::Camera(std::string topic, std::string name, int min_period, int max_period)
       : PublishingDevice(topic, name, min_period), _max_period(max_period) {}

void Camera::add_image(std::string image)
{
    _images.push_back(image);
}

void Camera::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);

    auto period_generator = std::bind(std::uniform_int_distribution<int>(_period, _max_period), 
                                      std::default_random_engine(time(nullptr)));
    period_generator();

    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::vector<std::vector<unsigned char>> images;
    images.reserve(_images.size());
    unsigned failed{0};
    for (unsigned i = 0; i < _images.size(); i++)
    {
        try
        {
            input.open(_images[i - failed], std::ios::binary);
            images.push_back(std::vector<unsigned char>());
            images[i - failed].assign(std::istreambuf_iterator<char>(input), {});
        }
        catch (std::ifstream::failure &e)
        {
            Log::warning("Camera '" + _name + "' error while reading file " + _images[i - failed] + 
                         " with: " + e.what());
            failed++;
        }

        input.close();
    }
    unsigned modulo{static_cast<unsigned>(_images.size() - failed)};
    if (modulo == 0)
    {
        Log::warning("Camera: '" + _name + "' has no images to send, terminating...");
        return;
    }
    unsigned index{0};

    future.wait_for(std::chrono::seconds(period_generator()));
    while (run)
    {
        message->set_payload(static_cast<void *>(&images[index % modulo][0]), images[index % modulo].size());
        index++;
        
        mutex.lock();
            client.publish(message);
        mutex.unlock();
        
        Log::log(_name + ": sending an image");
        future.wait_for(std::chrono::seconds(period_generator()));
    }
}
