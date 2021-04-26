#include "login_view.h"
#include "ui_login.h"
#include "program.h"

LoginView::LoginView(LoginWidgetModel *login_widget_model, ConnectionController *connection_cotroller)
      : QMainWindow(nullptr), _ui(new Ui::Login), _login_widget_model(login_widget_model), 
        _connection_controller(connection_cotroller)
{
    _ui->setupUi(this);

    _login_widget_model->setParent(this);

    //TODO add true/false to start clean session
    //TODO add text with connection ID
    _ui->protocol->addItem("tcp://");
    _ui->protocol->addItem("mqtt://");
    _ui->host->setText("test.mosquitto.org");
    _ui->port->setText("1883");
    _ui->user->setText("");
    _ui->password->setText("");
}

LoginView::~LoginView()
{
    delete _ui;
}

void LoginView::on_connect_clicked()
{   
    Log::log("On connected clicked.");
    std::string server_address = (_ui->protocol->currentIndex() == 0 ? "tcp://" : "") +
                                  _ui->host->text().toStdString() + ":" + _ui->port->text().toStdString();

    //TODO start login countdown - loading cirle

    Log::log("Calling connect.");
    _connection_controller->connect(server_address, "id_123_ab", _ui->user->text().toStdString(), 
                                    _ui->password->text().toStdString(), true);
    
    //TODO remove just a demonstration
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //_connection_controller->disconnect();
}

