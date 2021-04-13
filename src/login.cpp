#include "login.h"
#include "messagepool.h"
#include "ui_mainwindow.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->protocol->addItem("mqtt://");
    ui->protocol->addItem("tcp://");
    ui->host->setText("localhost");
    ui->port->setText("1883");
}

Login::~Login()
{
    delete ui;
}

void Login::on_connect_clicked()
{
    //call client connect function
    if (true) {
        this->hide();
        auto mp = new MessagePool(nullptr);
        mp->show();
    } else {

    }
}
