
/**
 * @file        program.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the Program class.
 **/

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

    _connection_controller = new ConnectionController(_mutex, this, &Program::connect_cb, &Program::disconnect_cb);
    _subscription_controller = new SubscriptionController();
    _message_controller = new MessageController(_tree_model);

    _main_view = new MainView(_tree_model, _connection_controller,
                                _message_controller, _subscription_controller);
    _login_view = new LoginView(_connection_controller);

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
            return;
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
        _client = new Client(server_address, id, FileType::ALL_AS_BINARY, 
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

        emit _connection_controller->connection_failed();
        return;
    }
    catch(...) {
        Log::error("Some error");
    }
    Log::log("Client created.");

    _message_controller->register_client(_client);
    _subscription_controller->register_client(_client);
    _connection_controller->register_client(_client);
    Log::log("Client registered.");

    _mutex->lock();
        Log::log("Connecting client...");

//        if (_client->connect(connection_options))
//        {
//            // TODO
//            emit _connection_controller->connection_failed();
//            return;
//        }
        try {
            _client->connect(connection_options);
        }  catch (const mqtt::exception& exc) {
            emit _connection_controller->connection_failed();
            Log::error("Connection failure.");
            return;
        }
        _mutex->lock(); // wait for connection to complete
        _mutex->unlock(); // open the mutex for next possible connection

    if (_connection_controller->get_connection_status())
    {
        Log::log("Switching windows...");

        Log::log("Closing login window...");
        _login_view->hide();
        Log::log("Login window hidden.");

        Log::log("Opening main window...");

        _main_view->display();
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
