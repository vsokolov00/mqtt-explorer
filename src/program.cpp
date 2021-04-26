
#include "program.h"

Program::~Program()
{
    delete _connection_controller;
    delete _subscription_controller;
    delete _main_view;
    delete _message_controller;
    delete _login_view;
    delete _mutex;
}

void Program::connect_cb(void *object, const std::string &server_address, const std::string &id, 
                         const mqtt::connect_options &connection_options)
{
    Program *program = static_cast<Program *>(object);
    program->connect(server_address, id, connection_options);
}

void Program::disconnect_cb(void *object)
{
    Program *program = static_cast<Program *>(object);
    program->disconnect();
}

void Program::init()
{
    Log::log("Program initialization starting...");
    _mutex = new std::mutex();

    _tree_model = new TreeModel(nullptr);
    _main_widget_model = new MainWidgetModel(nullptr);
    _login_widget_model = new LoginWidgetModel(nullptr);

    _connection_controller = new ConnectionController(_mutex, this, &Program::connect_cb, &Program::disconnect_cb,
                                                      _main_widget_model, _login_widget_model);
    _subscription_controller = new SubscriptionController(_main_widget_model);
    _message_controller = new MessageController(_tree_model, _main_widget_model);

    _main_view = new MainWindow(_tree_model, _main_widget_model, _connection_controller, 
                                _message_controller, _subscription_controller);
    _login_view = new Login(_login_widget_model, _connection_controller);

    Log::log("Program initialization complete.");
}

void Program::start()
{
    _login_view->show();
}

void Program::quit()
{
    if (_client != nullptr)
    {
        if (_client->disconnect())
        {
            Log::error("Disconnection failed.");
            delete _client;
        }
        _mutex->lock();
        delete _client;
    }
}

void Program::connect(const std::string &server_address, const std::string &id, 
                                 const mqtt::connect_options &connection_options)
{
    Log::log("Creating client with server address " + server_address);

    try
    {
        _client = new Client(server_address, id, FileType::ALL, 
                             _connection_controller, &ConnectionController::on_connection_success_cb, 
                             &ConnectionController::on_connection_failure_cb, &ConnectionController::on_connection_lost_cb,
                             &ConnectionController::on_disconnection_success_cb, 
                             &ConnectionController::on_disconnection_failure_cb,
                             _message_controller, &MessageController::on_message_arrived_cb, 
                             &MessageController::on_delivery_complete_cb,
                             &MessageController::on_publish_success_cb, &MessageController::on_publish_failure_cb,
                             _subscription_controller, &SubscriptionController::on_subscribe_success_cb,
                             &SubscriptionController::on_subscribe_failure_cb, SubscriptionController::on_unsubscribe_success_cb,
                             &SubscriptionController::on_unsubscribe_failure_cb);
    }
    catch (const std::bad_alloc &e)
    {
        (void)e;
        this->~Program();
        exit(99);
    }
    catch (const mqtt::exception &e)
    {
        Log::error("Wrong server address data: " + std::string(e.what()));
        _login_widget_model->connection_failed();
        return;
    }
    Log::log("Client created.");

    _message_controller->register_client(_client);
    _subscription_controller->register_client(_client);
    _connection_controller->register_client(_client);
    Log::log("Client registered.");

    _mutex->lock();
        Log::log("Connecting client...");
        if (_client->connect(connection_options))
        {
            // TODO
            _login_widget_model->connection_failed();
            return;
        }

    _mutex->lock(); // wait for connection to complete

    if (_connection_controller->get_connection_status())
    {
        Log::log("Switching windows...");

        Log::log("Closing login window...");
        _login_view->hide();
        Log::log("Login window hidden.");

        Log::log("Opening main window...");
        _main_view->show();
        Log::log("Main window opened.");
    }
}

void Program::disconnect()
{
    _mutex->lock();
    delete _client;
    _client = nullptr;

    _mutex->unlock();
    _main_view->hide();
    _login_view->show();
}
