
#include "runner.h"

Runner::Runner(Devices &devices, const std::string server_address)
             : _thermometer_runner(devices.thermometers, server_address) 
{
    not_runable = _thermometer_runner.not_runable;
}

void Runner::run_threads()
{
    _thermometer_runner.run_thermometers();
}

void Runner::stop_threads()
{
    _thermometer_runner.stop_thermometers();
}
