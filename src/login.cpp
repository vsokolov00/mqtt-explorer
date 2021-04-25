#include "login.h"
#include "ui_login.h"
#include "program.h"

Login::Login() : QMainWindow(nullptr), _ui(new Ui::Login)
{
    _ui->setupUi(this);
    //TODO add true/false to start clean session
    //TODO add text with connection ID
    _ui->protocol->addItem("tcp://");
    _ui->protocol->addItem("mqtt://");
    _ui->host->setText("localhost");
    _ui->port->setText("1883");
    _ui->user->setText("admin");
    _ui->password->setText("admin");
}

Login::~Login()
{
    delete _ui;
}

void Login::get_login_info(Program *program)
{
    this->show();
    connect(this, &Login::login_info_entered, program, &Program::login_info_entered_cb);
}

void Login::on_connect_clicked()
{   
    Log::log("On connected clicked.");
    _server_address = (_ui->protocol->currentIndex() == 0 ? "tcp://" : "mqtt://") + _ui->host->text().toStdString() + ":"
                                                                                 + _ui->port->text().toStdString();

    _id = "id_123_ab"; //TODO
    _connection_options.set_clean_session(true);
    //connection_options.set_user_name(_ui->user->text().toStdString());
    //connection_options.set_password(_ui->password->text().toStdString());

    login_info_entered();

    //TODO start login countdown - loading cicrle
}

mqtt::connect_options Login::get_connection_options() const
{
    return _connection_options;
}

std::string Login::get_server_address() const
{
    return _server_address;
}

std::string Login::get_id() const
{
    return _id;
}

void Login::connection_failed(bool connection_exist, const std::string &server_address)
{   
    (void)connection_exist;
    (void)server_address;
    // TODO display red message to the user that login to server adddress failed - try again...
    // if the connection_exist is true, then inform also about this
}

void Login::connection_failed()
{
    //TODO display red message
}
