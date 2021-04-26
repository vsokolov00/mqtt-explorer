#include "connection_controller.h"

ConnectionController::ConnectionController(std::mutex *mutex, CBObject connection_object, ConnectCB connection_cb, 
                                           DisconnectCB disconnect_cb, MainWidgetModel *main_widget_model, 
                                           LoginWidgetModel *login_widget_model) 
                     : _mutex(mutex), _connection_object(connection_object), _connection_cb(connection_cb),
                       _disconnect_cb(disconnect_cb), _main_widget_model(main_widget_model), 
                       _login_widget_model(login_widget_model) {}

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

bool ConnectionController::get_connection_status()
{
    return _connection_status;
}

void ConnectionController::on_connection_success(const std::string &cause)
{
    (void)cause;
    Log::log("Connection succeeded.");
    
    if (!_reconnect)
    {
        _connection_status = true;
        _mutex->unlock();
    }
}

void ConnectionController::on_connection_failure(const mqtt::token &token)
{
    Log::log("Connection failed.");

    if (!_reconnect)
    {
        _login_widget_model->connection_failed(token.get_connect_response().is_session_present(), 
                                               std::string(token.get_connect_response().get_server_uri()));
        _connection_status = false;
        _mutex->unlock();
    }
    else
    {
        _main_widget_model->reconnect_failed(token.get_connect_response().is_session_present(), 
                                             std::string(token.get_connect_response().get_server_uri()));
    }
}

void ConnectionController::on_disconnection_success(const mqtt::token &token)
{
    (void)token;
    Log::log("Disconnection succeeded.");

    _mutex->unlock();
}

void ConnectionController::on_disconnection_failure(const mqtt::token &token)
{
    (void)token;
    Log::error("Disconnection failed.");

    _mutex->unlock();
}

void ConnectionController::on_connection_lost(const std::string &cause)
{
    (void)cause;
    Log::log("Connection lost.");
    _main_widget_model->connection_lost();
}

void ConnectionController::register_client(Client *client)
{
    _client = client;
}

void ConnectionController::connect(const std::string &server_address, const std::string &id, const std::string &user_name, 
                                   const std::string &password, bool clean_session)
{
   _connection_options.set_clean_session(clean_session);
   _connection_options.set_user_name(user_name);
   _connection_options.set_password(password);

   _connection_cb(_connection_object, server_address, id, _connection_options);
}

void ConnectionController::disconnect()
{
    if (_client->disconnect())
    {
        Log::error("Disconnection failed.");
        _mutex->unlock();
    }
    _disconnect_cb(_connection_object);
}

void ConnectionController::reconnect()
{
    _reconnect = true;
    if (_client->connect(_connection_options))
    {
        _main_widget_model->reconnect_failed();
    }
}

void ConnectionController::go_to_login_view()
{
    _mutex->unlock();
    _disconnect_cb(_connection_object);
}
