
/**
 * @file        login_view.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the LoginView class.
 **/

#include "login_view.h"
#include "ui_login.h"
#include "program.h"

LoginView::LoginView(ConnectionController *connection_cotroller)
      : QMainWindow(nullptr), _ui(new Ui::Login),
        _connection_controller(connection_cotroller)
{
    _ui->setupUi(this);

    _ui->protocol->addItem("tcp://");
    _ui->protocol->addItem("mqtt://");
    _ui->host->setText("localhost");
    _ui->port->setText("1883");
    _ui->user->setText("");
    _ui->password->setText("");
    _ui->clean_session->setChecked(true);
    _ui->connection_id->setText("");

    _pop_up = new PopUp();
}

LoginView::~LoginView()
{
    delete _pop_up;
    delete _ui;
}

void LoginView::on_connect_clicked()
{   
    Log::log("On connected clicked.");
    std::string server_address = (_ui->protocol->currentIndex() == 0 ? "tcp://" : "") +
                                  _ui->host->text().toStdString() + ":" + _ui->port->text().toStdString();

    Log::log("Calling connect.");
    _connection_controller->connect(server_address, _ui->connection_id->text().toStdString(), _ui->user->text().toStdString(),
                                    _ui->password->text().toStdString(), _ui->clean_session->checkState());

    connect(_connection_controller, SIGNAL(connection_failed()), this, SLOT(connection_failure_popup_set()));
}

void LoginView::show_popup()
{
    auto window_size = this->size();
    auto app_position =  this->mapToGlobal(this->pos());
    auto popup_size = _pop_up->size();
    _pop_up->setGeometry(app_position.x() / 2 + window_size.rwidth() - (popup_size.rwidth()+30),
                        app_position.y() / 2 + 20, popup_size.rwidth(), popup_size.rheight());
    _pop_up->show();
}

void LoginView::connection_failure_popup_set()
{

    _pop_up->set_pop_up("Connection failed.", false);

    show_popup();
}


