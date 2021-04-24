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
    delete message_controller;
    delete conn_controller;
}

void MainWindow::init_models()
{
    main_model = new TreeModel(this);
    ui->messageList->setModel(main_model);
    message_controller = new MessageController(*main_model);
    //some built-in QT stuff for selection of treeview items
    connect(ui->messageList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::item_selection);
}

void MainWindow::init_controllers()
{
    message_controller = new MessageController(*main_model);
    conn_controller = new ConnectionController();
    sub_constroller = new SubscriptionController();
}

void MainWindow::login()
{
    auto l = new Login(this, conn_controller);
    l->show();
    connect(l, &Login::login_successfull, this, &MainWindow::show_main_window);
}


void MainWindow::show_main_window()
{       
    this->show();
    ui->messageList->setColumnWidth(0, ui->messageList->size().rwidth() * 0.6);
    ui->img_label->setVisible(false);
    ui->listWidget->setWrapping(false);
    ui->clear->setVisible(false);
}

void MainWindow::item_selection()
{
    ui->listWidget->clear();
    const bool hasCurrent = ui->messageList->selectionModel()->currentIndex().isValid();

    if (hasCurrent)
    {
        auto qindex = ui->messageList->selectionModel()->currentIndex();
        auto item = main_model->getItem(qindex);
        auto history = item->getMessages();
        QStringList messages;

        for (auto [message, type] : history)
        {
            auto tmp = type + ": " + message.toString();
            messages << tmp;
        }
        ui->listWidget->addItems(messages);
        ui->listWidget->update();
        ui->path->setText(main_model->getPath(*item));
    }
}

void MainWindow::on_publish_clicked()
{
    QString topic = ui->path->text();
    QVariant qv = ui->msg_to_publish->toPlainText();

    if (message_controller->publish_msg(topic.toStdString(), ui->msg_to_publish->toPlainText()))
    {
        item_selection();
        emit on_clear_clicked();

    }
}

void MainWindow::on_subscribe_clicked()
{
    std::cout << "Subscribe" << std::endl;
}

void MainWindow::on_unsubscribe_clicked()
{
    std::cout << "Unubscribe" << std::endl;
}

void MainWindow::on_chooseFile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose the message content", QDir::homePath(), tr("Messages (*.png *.xml *.jpg *.json *.txt)"));
    QFile file(file_name);
    QFileInfo info_file(file_name);
    QByteArray msg;

    QString type = info_file.completeSuffix();

    if (type == "jpg" || type == "png")
    {
        //binary
        QImage img;
        QImageReader reader(file_name);

        if(reader.read(&img))
        {
            // display chosen image
            int w = ui->img_label->width();
            int h = ui->img_label->height();
            QPixmap image = QPixmap::fromImage(img);

            ui->img_label->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
            ui->img_label->setVisible(true);
            ui->msg_to_publish->setVisible(false);
            //----------------------
            QBuffer buffer(&msg);
            buffer.open(QIODevice::WriteOnly);
            img.save(&buffer);

            message_controller->set_message(QVariant(msg), FileType::IMAGE);
            message_controller->set_file_chosen();
            ui->clear->setVisible(true);
        }
    }
    else if (type == "json" || type == "xml")
    {
        //markup
    }
    else
    {
        //plain text
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {

        }
        QTextStream in(&file);
        QStringList message;
        message << in.readAll();

        ui->msg_to_publish->setPlainText(message.join("\n"));
    }
}


void MainWindow::on_clear_clicked()
{
    message_controller->set_message({}, FileType::NONE);\
    message_controller->set_file_not_chosen();

    ui->img_label->setVisible(false);
    ui->msg_to_publish->setPlainText("");
    ui->msg_to_publish->setVisible(true);
}
