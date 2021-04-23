#include "messagepool.h"
#include "ui_messagepool.h"

#include <QApplication>

MessagePool::MessagePool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MessagePool)
{
    ui->setupUi(this);
    model = new TreeModel(this);
    ui->messageList->setModel(model);
    engine = new TopicsEngine(*model);

    connect(ui->messageList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MessagePool::item_selection);

    this->display_message_tree();
}

MessagePool::~MessagePool()
{
    delete ui;
}

void MessagePool::display_message_tree()
{       
    ui->messageList->setColumnWidth(0, ui->messageList->size().rwidth() * 0.6);
    this->show();
}

void MessagePool::on_pushButton_3_clicked()
{
    QString s = ui->message->text();
    QVariant qv = QVariant(s);

    engine->recieve_message(ui->topic->text().toStdString(), qv);
    item_selection();
}

void MessagePool::item_selection()
{
    ui->listWidget->clear();
    const bool hasCurrent = ui->messageList->selectionModel()->currentIndex().isValid();

    if (hasCurrent)
    {
        auto qindex = ui->messageList->selectionModel()->currentIndex();
        auto item = model->getItem(qindex);
        QVector<QVariant> history = item->getMessages();
        QStringList messages;

        for (auto& message : history)
        {
            messages << message.toString();
        }
        ui->listWidget->addItems(messages);
        ui->listWidget->update();
        ui->path->setText(item->getPath());
    }
}



void MessagePool::on_pushButton_clicked()
{
    QString topic = ui->path->text();
    QVariant qv = ui->message->text();

    engine->recieve_message(topic.toStdString(), qv);
    item_selection();
}
