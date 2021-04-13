#include "messagepool.h"
#include "ui_messagepool.h"

#include <QApplication>

MessagePool::MessagePool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessagePool)
{
    ui->setupUi(this);
    display_message_tree();
}

MessagePool::~MessagePool()
{
    delete ui;
}

void MessagePool::display_message_tree()
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    ui->messageList->setModel(model);

}
