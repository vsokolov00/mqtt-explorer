
#include "runner.h"

Runner::Runner(Devices &devices, const std::string server_address)
       : _thermometer_runner(devices.thermometers, &Thermometer::run, server_address, "id_1"),//"thermometers_id_135448"), 
         _hygrometer_runner(devices.hygrometers, &Hygrometer::run, server_address, "id_2"),//"hygrometers_id_7135454"),
         _wattmeter_runner(devices.wattmeters, &Wattmeter::run, server_address, "id_3"),//"wattmeters_id_871159"),
         _move_sensor_runner(devices.move_sensors, &MoveSensor::run, server_address, "id_4")//"move_sensors_id_164813")
{
    not_runable = _thermometer_runner.not_runable | _hygrometer_runner.not_runable | _wattmeter_runner.not_runable;
}

void Runner::run_threads()
{
    _thermometer_runner.run_devices();
    _hygrometer_runner.run_devices();
    _wattmeter_runner.run_devices();
    _move_sensor_runner.run_devices();
}

void Runner::stop_threads()
{
    _thermometer_runner.stop_devices();
    _hygrometer_runner.stop_devices();
    _wattmeter_runner.stop_devices();
    _move_sensor_runner.stop_devices();
}

template<class T, class U> DeviceRunner<T, U>::DeviceRunner(std::vector<T> &devices, U function, const std::string &server_address, const std::string &id)
                                              : _devices(devices), _function(function), _client(server_address, id)
{
    mqtt::connect_options connection_opts;
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

template<class T, class U> void DeviceRunner<T, U>::run_devices()
{
    _run = true;

    _threads.reserve(_devices.size());
    _promises.reserve(_devices.size());

    for (unsigned i = 0; i < _devices.size(); i++)
    {
        _promises.push_back(std::promise<void>());
        _threads.push_back(std::thread(_function, _devices[i], 
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
