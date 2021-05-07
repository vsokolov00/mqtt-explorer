
/**
 * @file        program.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz                    <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the Program class.
 **/

#include "program.h"

std::string Program::CONFIG_FILE = "config.json";

Program::~Program()
{
    delete _tree_model;
    delete _connection_controller;
    delete _subscription_controller;
    delete _message_controller;
    delete _main_view;
    delete _login_view;
    delete _mutex;
    delete _flow_layout;
    delete _dashboard_controller;
    delete _dashboard_view;
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
    _flow_layout = new FlowLayout();
    
    _tree_model = new TreeModel(nullptr);

    _connection_controller = new ConnectionController(_mutex, this, &Program::connect_cb, &Program::disconnect_cb);
    _subscription_controller = new SubscriptionController();
    _dashboard_controller = new DashboardController();
    _message_controller = new MessageController(_tree_model, _dashboard_controller);

    _main_view = new MainView(_tree_model, _connection_controller, _message_controller, 
                              _subscription_controller, _dashboard_controller);
    _login_view = new LoginView(_connection_controller);
    _dashboard_view = new DashboardView(_dashboard_controller, _flow_layout);

    _dashboard_controller->register_dashboard_view(_dashboard_view);

    Log::log("Program initialization complete.");
}

void Program::start()
{
    _login_view->show();
}

void Program::quit()
{
    save_configuration();

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

    try 
    {
        _client->connect(connection_options);
    }  
    catch (const mqtt::exception& exc) 
    {
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

        Log::log("Loading Dashboard devices...");
        load_configuration();
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

void Program::load_configuration()
{
    _config_loaded = true;
    std::ifstream file(CONFIG_FILE, std::ifstream::in);
    if (file.fail())
    {
        Log::warning("Opening configuration file '" + CONFIG_FILE + "' failed. Dashboard was not loaded.\n"
                     "New confuguration file 'config.json' will be created at termination.");
        Program::CONFIG_FILE = "config.json";
        return;
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    std::string content = stream.str();
    file.close();

    std::string errs;
    Json::Value root;
    Json::CharReader *reader = Json::CharReaderBuilder().newCharReader();
    if (reader == nullptr)
    {
        Log::error("Unable to allocate resources.\nDashboard was not loaded and newly added devices will not be saved.");
        return;
    }

    if (!reader->parse(content.c_str(), content.c_str() + content.size(), &root, &errs))
    {
        Log::error("JSON configuration file parsing failed with:\n" + errs + "\nDashboard was not loaded.");
        delete reader;
        return;
    }
    delete reader;

    root = root["devices"];

    DeviceWidget *device = nullptr;
    for (unsigned i = 0; root[i]; i++)
    {
        device = new DeviceWidget(_dashboard_view, static_cast<DeviceType>(root[i]["type"].asUInt()), 
                                  QString(root[i]["name"].asCString()), QString(root[i]["topic"].asCString()));
        _flow_layout->addWidget(device);
        _dashboard_controller->add_device(device);
    }
}

void Program::save_configuration()
{
    if (!_config_loaded)
    {
        return;
    }
    
    Json::Value root;
    Json::StreamWriter *writer = Json::StreamWriterBuilder().newStreamWriter();
    if (writer == nullptr)
    {
        Log::error("Unable to allocate resources to save configuration file. All newly added devices are lost.");
        return;
    }
    std::ostringstream stream;

    root["devices"] = Json::arrayValue;
    std::map<std::string, DeviceWidget*>::iterator iterator = _dashboard_controller->topic_to_device.begin();
    for (unsigned i = 0; iterator != _dashboard_controller->topic_to_device.end(); i++, iterator++)
    {
        root["devices"][i]["name"] = iterator->second->get_name();
        root["devices"][i]["topic"] = iterator->second->get_topic();
        root["devices"][i]["type"] = static_cast<unsigned>(iterator->second->get_type());
    }

    std::ofstream file(CONFIG_FILE, std::ofstream::out);
    if (file.fail())
    {
        Log::error("Opening configuration file '" + CONFIG_FILE + "' failed. All newly added devices are lost.");
        delete writer;
        return;
    }

    try
    {
        writer->write(root, &file);
    }
    catch(const std::exception &e)
    {
        (void)e;
        Log::error("Unable to save configuration file. All newly added devices will be lost.");
    }

    file.close();
    if (file.fail())
    {
        Log::error("Unable to save configuration file. All newly added devices will be lost.");
    }
    delete writer;
}   
