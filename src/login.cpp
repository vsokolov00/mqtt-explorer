#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent, ConnectionController *cc)
    : QMainWindow(parent),
      ui(new Ui::Login),
      cc(cc)
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
    if (cc->connect(ui->protocol->currentIndex(),
                    ui->host->text().toStdString(),
                    ui->port->text().toStdString(),
                    ui->user->text().toStdString(),
                    ui->password->text().toStdString()))
    {
        emit login_successfull();
        this->hide();
    }
    else
    {
        //unsuccessful log in
    }
}
