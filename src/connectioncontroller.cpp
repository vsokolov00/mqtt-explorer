#include "connectioncontroller.h"

ConnectionController::ConnectionController(std::mutex *mutex) : _mutex(mutex) {}

void ConnectionController::on_connection_success_cb(void *object, const std::string &cause)
{
    ConnectionController *connection_controller = static_cast<ConnectionController *>(object);
    connection_controller->on_connection_success(cause);
}

void ConnectionController::on_connection_lost_cb(void *object, const std::string &cause)
{
    ConnectionController *connection_controller = static_cast<ConnectionController *>(object);
    connection_controller->on_connection_lost(cause);
}

void ConnectionController::on_connection_failure_cb(void *object, const mqtt::token &token)
{
    ConnectionController *connection_controller = static_cast<ConnectionController *>(object);
    connection_controller->on_connection_failure(token);
}

void ConnectionController::on_disconnection_success_cb(void *object, const mqtt::token &token)
{
    ConnectionController *connection_controller = static_cast<ConnectionController *>(object);
    connection_controller->on_disconnection_success(token);
}
void ConnectionController::on_disconnection_failure_cb(void *object, const mqtt::token &token)
{
    ConnectionController *connection_controller = static_cast<ConnectionController *>(object);
    connection_controller->on_disconnection_failure(token);
}

void ConnectionController::on_connection_success(const std::string &cause)
{
    (void)cause;
    Log::log("Connection success.");

    _connection_success = true;
    _mutex->unlock();
}

void ConnectionController::on_connection_failure(const mqtt::token &token)
{
    Log::log("Connection failure.");

    _connection_exist = token.get_connect_response().is_session_present();
    _server_address = std::string(token.get_connect_response().get_server_uri());
    _connection_success = false;
    _mutex->unlock();
}

void ConnectionController::on_disconnection_success(const mqtt::token &token)
{
    (void)token;
    //TODO
}

void ConnectionController::on_disconnection_failure(const mqtt::token &token)
{
    (void)token;
    //TODO
}

void ConnectionController::on_connection_lost(const std::string &cause)
{
    (void)cause;
    Log::log("Connection lost.");
    //TODO
    //_main_window->connection_lost();
}


bool ConnectionController::get_connection_status()
{
    return _connection_success;
}

bool ConnectionController::get_connection_existance()
{
    return _connection_exist;
}

std::string ConnectionController::get_server_address() const
{
    return _server_address;
}
