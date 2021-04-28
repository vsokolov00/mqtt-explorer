#include "main_view.h"
#include "ui_mainwindow.h"
#include <iostream>

MainView::MainView(TreeModel *tree_model, ConnectionController *connection_controller,
                       MessageController *message_controller, SubscriptionController *subscription_controller) 
           : QMainWindow(nullptr), _ui(new Ui::MainWindow), _tree_model(tree_model),
             _connection_controller(connection_controller), _message_controller(message_controller), 
             _subscription_controller(subscription_controller)
{
    Log::log("Main window initialization starting...");
    
    _tree_model->setParent(this);

    pop_up = new PopUp(this);

    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");

    _ui->setupUi(this);
    _ui->messageList->setModel(_tree_model);

    connect(_ui->messageList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainView::item_selection);
    connect(_message_controller, &MessageController::message_arrived, this, &MainView::item_selection);
    connect(_message_controller, &MessageController::publish_success, this, &MainView::publish_success_popup_set);
    connect(_message_controller, &MessageController::publish_failure, this, &MainView::publish_failure_popup_set);
    connect(_subscription_controller, SIGNAL(subscription_success(QString)), this, SLOT(subscribe_success_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(unsubscription_success(QString)), this, SLOT(unsubscribe_success_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(subscription_failure(QString)), this, SLOT(subscribe_failure_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(unsubscription_failure(QString)), this, SLOT(unsubscribe_failure_popup_set(QString)));
    connect(_connection_controller, SIGNAL(connection_failed(QString,bool)), this, SLOT(connection_failure_popup_set(QString,bool)));
    connect(_connection_controller, SIGNAL(connection_success()), this, SLOT(connection_success_popup_set()));
    //connect(_connection_controller, SIGNAL(connection_failed()), this, SLOT(connection_failure_popup_set()));

    Log::log("Main window initialization complete.");
}

MainView::~MainView()
{
    delete _ui;
}

void MainView::display()
{
    this->show();
    _ui->messageList->setColumnWidth(0, _ui->messageList->size().width() * 0.6);
    _ui->img_label->setVisible(false);
    _ui->listWidget->setWrapping(false);
    _ui->clear->setVisible(false);
}

void MainView::item_selection()
{
    _ui->listWidget->clear();
    const bool hasCurrent = _ui->messageList->selectionModel()->currentIndex().isValid();

    if (hasCurrent)
    {
        auto qindex = _ui->messageList->selectionModel()->currentIndex();
        auto item = _tree_model->getItem(qindex);
        auto history = item->getMessages();
        QStringList messages;

        for (std::tuple<QVariant, QString> &tuple : history)
        {
            auto tmp = std::get<1>(tuple) + ": " + std::get<0>(tuple).toString();
            messages << tmp;
        }
        _ui->listWidget->addItems(messages);
        _ui->listWidget->update();
        _ui->path->setText(_tree_model->getPath(*item));
    }
}

void MainView::on_publish_clicked()
{
    QString topic = _ui->path->text();
    QVariant qv = _ui->msg_to_publish->toPlainText();

    _message_controller->publish(topic.toStdString(), _ui->msg_to_publish->toPlainText().toStdString());
}

void MainView::on_subscribe_clicked()
{
    std::string topic = _ui->topic->text().toStdString();
    Log::log("Subscribing to topic: " + topic);
    _subscription_controller->subscribe(topic, 1);
}


void MainView::on_unsubscribe_clicked()
{
    std::string topic = _ui->topic->text().toStdString();
    Log::log("Unsubscribing to topic: " + topic);
    _subscription_controller->unsubscribe(topic);
}

void MainView::on_disconnect_clicked()
{
    _connection_controller->disconnect();
}

void MainView::on_reconnect_clicked()
{
    _connection_controller->reconnect();
}

void MainView::on_chooseFile_clicked()
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
            int w = _ui->img_label->width();
            int h = _ui->img_label->height();
            QPixmap image = QPixmap::fromImage(img);

            _ui->img_label->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
            _ui->img_label->setVisible(true);
            _ui->msg_to_publish->setVisible(false);
            //----------------------
            file.open(QIODevice::ReadOnly);
            msg = file.readAll();

            _message_controller->set_message(QVariant(msg), FileType::ALL_IMAGES);
            _message_controller->set_file_chosen();
            _ui->clear->setVisible(true);
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

        _ui->msg_to_publish->setPlainText(message.join("\n"));
    }
}


void MainView::on_clear_clicked()
{
    //message_controller->set_message({}, FileType::ALL);
//    message_controller->set_file_not_chosen();

    _ui->img_label->setVisible(false);
    _ui->msg_to_publish->setPlainText("");
    _ui->msg_to_publish->setVisible(true);
}

void MainView::on_exit_clicked()
{
    _connection_controller->go_to_login_view();
}

void MainView::publish_success_popup_set()
{
    QString text = "Message published successfully!";
    pop_up->set_pop_up(text, true);
    show_popup();
}

void MainView::publish_failure_popup_set()
{
    QString text = "Message was not published!";
    pop_up->set_pop_up(text, false);
    show_popup();
}

void MainView::subscribe_success_popup_set(QString s)
{
    pop_up->set_pop_up("Successful subscription to topic: " + s, true);
    show_popup();
}

void MainView::subscribe_failure_popup_set(QString s)
{
    pop_up->set_pop_up("Unsuccessful subscription to topic: " + s, false);
    show_popup();
}

void MainView::unsubscribe_success_popup_set(QString s)
{
    pop_up->set_pop_up("Successful UNsubscription to topic: " + s, true);
    show_popup();
}

void MainView::unsubscribe_failure_popup_set(QString s)
{
    pop_up->set_pop_up("Unsuccessful UNsubscription to topic: " + s, false);
    show_popup();
}


void MainView::show_popup()
{
    auto window_size = this->size();
    auto app_position =  this->mapToGlobal(this->pos());
    auto popup_size = pop_up->size();
    pop_up->setGeometry(app_position.x() / 2 + window_size.rwidth() - (popup_size.rwidth() + 30),
                        app_position.y() / 2 + 20, popup_size.rwidth(), popup_size.rheight());
    pop_up->show();
}

void MainView::connection_lost_dialog()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Connection was lost", "Try to reconnect?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Log::log("Trying to reconnect.");
        _connection_controller->reconnect();
    }
    else
    {
        Log::log("Disconnect from the server.");
        _connection_controller->go_to_login_view();
    }
}

void MainView::reconnection_failed_dialog()
{
    //TODO display a window reconnect failed with reconnect button and got to login page
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reconnection failed", "Try again?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Log::log("Trying to reconnect...");
        _connection_controller->reconnect();
    }
    else
    {
        Log::log("Disconnecting from the server...");
        _connection_controller->go_to_login_view();
    }
}

void MainView::connection_failure_popup_set(QString s, bool connection_exist)
{
    if (connection_exist)
    {
        pop_up->set_pop_up("Connection to the " + s + " server failed. \nConnection already exists.", false);
    }
    else
    {
        pop_up->set_pop_up("Connection to the " + s + " server failed.", false);
    }

    show_popup();
}

void MainView::connection_failure_popup_set()
{
    pop_up->set_pop_up("Connection failed.", false);
    show_popup();
}

void MainView::connection_success_popup_set()
{
    pop_up->set_pop_up("Connection is successful!\nSession started..", true);
    show_popup();
}

