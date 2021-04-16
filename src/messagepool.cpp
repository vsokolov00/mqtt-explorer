#include "messagepool.h"
#include "ui_messagepool.h"

#include <QApplication>

MessagePool::MessagePool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessagePool)
{
    ui->setupUi(this);
    model = new TreeModel(this);
    display_message_tree();
    engine = new TopicsEngine(*model);
}

MessagePool::~MessagePool()
{
    delete ui;
}

void MessagePool::display_message_tree()
{       
    ui->messageList->setColumnWidth(0, ui->messageList->size().rwidth() * 0.6);
    ui->messageList->setModel(model);
    this->show();

}

void MessagePool::on_pushButton_clicked()
{
    engine->send_message("hello/mytopic/vlad", "nullptr");
}

void MessagePool::on_pushButton_2_clicked()
{
    engine->send_message("hello/mytopic/gfg", "mymessage");
}

void MessagePool::on_pushButton_3_clicked()
{
    engine->send_message("gaga/mynewtopichey/gfg", "hello");
}
