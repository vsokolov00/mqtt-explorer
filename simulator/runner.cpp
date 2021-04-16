
#include "runner.h"

Runner::Runner(Devices &devices, const std::string server_address)
       : _thermometer_runner(devices.thermometers, &Thermometer::run, server_address, "id_1"),
         _hygrometer_runner(devices.hygrometers, &Hygrometer::run, server_address, "id_2"),
         _wattmeter_runner(devices.wattmeters, &Wattmeter::run, server_address, "id_3"),
         _move_sensor_runner(devices.move_sensors, &MoveSensor::run, server_address, "id_4"),
         _light_runner(devices.lights, &Light::run, server_address, "id_5"),
         _reciever(server_address, "id_6") 
{
    _reciever.register_lights(devices.lights);
}

bool Runner::start()
{
    mqtt::connect_options options;

    try
    {
        options.set_clean_session(true);

        _thermometer_runner.connect_clients(options);
        _hygrometer_runner.connect_clients(options);
        _wattmeter_runner.connect_clients(options);
        _move_sensor_runner.connect_clients(options);
        _light_runner.connect_clients(options);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Connection was not established: " << exc.what() << std::endl;
        _thermometer_runner.disconnect_clients();
        _hygrometer_runner.disconnect_clients();
        _wattmeter_runner.disconnect_clients();
        _move_sensor_runner.disconnect_clients();
        _light_runner.disconnect_clients();

        return true;
    } 
    
    _thermometer_runner.run_devices();
    _hygrometer_runner.run_devices();
    _wattmeter_runner.run_devices();
    _move_sensor_runner.run_devices();
    _light_runner.run_devices();

    if (_reciever.start_recieving(options))
    {
        return true;
    }

    return false;
}

void Runner::stop()
{
    _reciever.stop_recieving();

    _thermometer_runner.stop_devices();
    _hygrometer_runner.stop_devices();
    _wattmeter_runner.stop_devices();
    _move_sensor_runner.stop_devices();
    _light_runner.stop_devices();

    _thermometer_runner.disconnect_clients();
    _hygrometer_runner.disconnect_clients();
    _wattmeter_runner.disconnect_clients();
    _move_sensor_runner.disconnect_clients();
    _light_runner.disconnect_clients();
}

template<class T, class U> DeviceRunner<T, U>::DeviceRunner(std::vector<T> &devices, U function, 
                                                            const std::string &server_address, const std::string &id)
                                              : _devices(devices), _function(function), _client(server_address, id) { }

template<class T, class U> void DeviceRunner<T, U>::run_devices()
{
    _run = true;

    _threads.reserve(_devices.size());
    _promises.reserve(_devices.size());

    for (unsigned i = 0; i < _devices.size(); i++)
    {
        _promises.push_back(std::promise<void>());
        _threads.push_back(std::thread(_function, std::ref(_devices[i]), 
                                      std::ref(_client), std::ref(_run), std::ref(_mutex), _promises[i].get_future()));
    }

}

template<class T, class U> void DeviceRunner<T, U>::stop_devices()
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

template<class T, class U> void DeviceRunner<T, U>::connect_clients(mqtt::connect_options connect_options)
{
    _client.connect(connect_options);
}

template<class T, class U> void DeviceRunner<T, U>::disconnect_clients()
{
    if (_client.is_connected())
    {
        try
        {
            _client.disconnect();
        }
        catch (const mqtt::exception& exc)
        {
            std::cerr << "Disconnect failed: " << exc.what() << std::endl;
        }
    }
}
