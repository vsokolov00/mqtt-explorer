
#include "program.h"

Program::~Program()
{
    delete _connection_controller;
    delete _subscription_controller;
    delete _main_view;
    delete _message_controller;
    delete _login_view;
    delete _client;
    delete _mutex;
}

void Program::init()
{
    Log::log("Program initialization starting...");
    _mutex = new std::mutex();

    _tree_model = new TreeModel(nullptr);
    _main_widget_model = new MainWidgetModel(nullptr);
    _login_widget_model = new LoginWidgetModel(nullptr);

    _connection_controller = new ConnectionController(_mutex);
    _subscription_controller = new SubscriptionController(_main_widget_model);
    _message_controller = new MessageController(_tree_model, _main_widget_model);

    _main_view = new MainWindow(_tree_model, _main_widget_model, _message_controller, _subscription_controller);
    _login_view = new Login(_login_widget_model, _connection_controller);

    Log::log("Program initialization complete.");
}

void Program::start()
{
    _login_view->get_login_info(this);
}

void Program::login_info_entered_cb()
{
    Log::log("Creating client with server address " + _login_view->get_server_address());

    try
    {
        _client = new Client(_login_view->get_server_address(), _login_view->get_id(), FileType::ALL, 
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
        _login_view->connection_failed();
        return;
    }

    _message_controller->register_client(_client);
    _subscription_controller->register_client(_client);
    Log::log("Client created.");

    _mutex->lock();
        Log::log("Connecting client...");
        if (_client->connect(_login_view->get_connection_options()))
        {
            _login_view->connection_failed();        
        }
    _mutex->lock();

    Log::log("Switching windows...");
    if (_connection_controller->get_connection_status())
    {
        Log::log("Closing login window...");
        _login_view->hide();
        Log::log("Login window hidden.");

        Log::log("Opening main window...");
        _main_view->show();
        Log::log("Main window opened.");
    }
    else
    {
        _login_view->connection_failed(_connection_controller->get_connection_existance(), 
                                       _connection_controller->get_server_address());
    }
}
