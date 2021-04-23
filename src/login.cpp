#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->protocol->addItem("mqtt://");
    ui->protocol->addItem("tcp://");
    ui->host->setText("localhost");
    ui->port->setText("1883");
    ui->user->setText("admin");
    ui->password->setText("admin");
}

Login::~Login()
{
    delete ui;
}


void Login::on_connect_clicked()
{
    if (ui->user->text() == "admin" && ui->password->text() == "admin") {
        emit login_successfull();
        this->hide();
    } else {
        //unsuccessful log in
    }
}
