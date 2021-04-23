#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete engine;
}

void MainWindow::create_controllers()
{
    model = new TreeModel(this);
    ui->messageList->setModel(model);

    engine = new MainController(*model);

    //some built-in QT stuff for selection of treeview items
    connect(ui->messageList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::item_selection);
}

void MainWindow::login()
{
    auto l = new Login(this);
    l->show();
    connect(l,&Login::login_successfull, this, &MainWindow::show);
}


void MainWindow::display_message_tree()
{       
    ui->messageList->setColumnWidth(0, ui->messageList->size().rwidth() * 0.6);
    this->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString s = ui->message->text();
    QVariant qv = QVariant(s);

    engine->recieve_message(ui->topic->text().toStdString(), qv);
    item_selection();
}

void MainWindow::item_selection()
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



void MainWindow::on_pushButton_clicked()
{
    QString topic = ui->path->text();
    QVariant qv = ui->message->text();

    engine->recieve_message(topic.toStdString(), qv);
    item_selection();
}

