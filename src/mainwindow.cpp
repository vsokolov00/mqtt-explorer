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
    delete main_model;
    delete main_controller;
}

void MainWindow::init_models()
{
    main_model = new TreeModel(this);
    ui->messageList->setModel(main_model);
    main_controller = new MainController(*main_model);
    //some built-in QT stuff for selection of treeview items
    connect(ui->messageList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::item_selection);
}

void MainWindow::init_controllers()
{
    main_controller = new MainController(*main_model);
}

void MainWindow::login()
{
    auto l = new Login(this);
    l->show();
    connect(l,&Login::login_successfull, this, &MainWindow::show_main_window);
}


void MainWindow::show_main_window()
{       
    this->show();
    ui->messageList->setColumnWidth(0, ui->messageList->size().rwidth() * 0.6);
}

void MainWindow::item_selection()
{
    ui->listWidget->clear();
    const bool hasCurrent = ui->messageList->selectionModel()->currentIndex().isValid();

    if (hasCurrent)
    {
        auto qindex = ui->messageList->selectionModel()->currentIndex();
        auto item = main_model->getItem(qindex);
        QVector<QVariant> history = item->getMessages();
        QStringList messages;

        for (auto& message : history)
        {
            messages << message.toString();
        }
        ui->listWidget->addItems(messages);
        ui->listWidget->update();
        //ui->path->setText(main_model->getPath(*item));
    }
}

//PUBLISH MESSAGE
void MainWindow::on_pushButton_clicked()
{
    QString topic = ui->path->text();
    QVariant qv = ui->msg_to_publish->toPlainText();

    main_controller->message_recieved(topic.toStdString(), qv, FileType::STRING_UTF8);
    item_selection();
}

//SUBSCRIBE TO THE TOPIC
void MainWindow::on_pushButton_2_clicked()
{
    std::cout << "Subscribe" << std::endl;
}
