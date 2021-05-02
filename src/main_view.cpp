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
    connect(_message_controller, &MessageController::publish_success, this, &MainView::on_clear_clicked);
    connect(_subscription_controller, SIGNAL(subscription_success(QString)), this, SLOT(subscribe_success_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(unsubscription_success(QString)), this, SLOT(unsubscribe_success_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(subscription_failure(QString)), this, SLOT(subscribe_failure_popup_set(QString)));
    connect(_subscription_controller, SIGNAL(unsubscription_failure(QString)), this, SLOT(unsubscribe_failure_popup_set(QString)));
    connect(_connection_controller, SIGNAL(connection_failed(QString,bool)), this, SLOT(connection_failure_popup_set(QString,bool)));
    connect(_connection_controller, SIGNAL(connection_success()), this, SLOT(connection_success_popup_set()));
    connect(_ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(display_full_message(QListWidgetItem*)));

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
        for (std::tuple<QVariant, QString, bool> &tuple : history)
        {
            QString tmp;
            auto type = std::get<1>(tuple);
            if (type == "image")
            {
                tmp = std::get<1>(tuple);
            }
            else if (type == "json")
            {
                tmp = std::get<1>(tuple);
            }
            else
            {
                tmp = std::get<1>(tuple) + ": " + std::get<0>(tuple).toString();
            }

             _ui->listWidget->addItem(tmp);
             auto item = _ui->listWidget->item(_ui->listWidget->count()-1);
            if (std::get<2>(tuple)) //if our message
            {
                item->setBackgroundColor(Qt::lightGray);
            }
        }
        _ui->listWidget->update();
        if (!_ui->path->hasFocus())
        {
            _ui->path->setText(_tree_model->getPath(*item));
        }
    }
}

void MainView::on_publish_clicked()
{
    QString topic = _ui->path->text();
    topic = _message_controller->validate_topic_path(topic);

    if (_message_controller->is_file_chosen())
    {
        auto tmp = _message_controller->get_message().toByteArray();
        _message_controller->publish(topic.toStdString(), tmp.toStdString());
    }
    else
    {
        auto msg = _ui->msg_to_publish->toPlainText().toStdString();
        _message_controller->publish(topic.toStdString(), msg);
    }
}

void MainView::on_subscribe_clicked()
{
    std::string topic = _ui->topic->text().toStdString();
    topic = _message_controller->validate_topic_path(QString::fromStdString(topic)).toStdString();

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
    QString file_name = QFileDialog::getOpenFileName(this, "Choose the message content", QDir::homePath(), tr("Messages (*.png *.jpg *.json *.txt)"));
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

            _message_controller->set_message(QVariant(msg));
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
    _message_controller->set_file_not_chosen();

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

void MainView::display_full_message(QListWidgetItem* clicked_item)
{
    Log::log("Displaying full message in new window");

    int i = _ui->listWidget->row(clicked_item);
    auto qindex = _ui->messageList->selectionModel()->currentIndex();
    auto item = _tree_model->getItem(qindex);
    auto history = item->getMessages();
    auto type = std::get<1>(history[i]);
    auto msg = std::get<0>(history[i]);

    if (type == "image")
    {
        QLabel* img = new QLabel(this);
        img->setWindowFlags(Qt::Window);
        auto tmp = msg.toByteArray();
        QPixmap pix;
        pix.loadFromData(tmp);
        img->setPixmap(pix);
        img->show();
    } else if (type == "text" || type == "binary") //WHY text is binary?? TODO
    {
        QLabel* img = new QLabel(this);
        img->setWindowFlags(Qt::Window);
        auto tmp = msg.toString();
        img->setText(tmp);
        img->show();
    } else if (type == "json")
    {
        QLabel *json = new QLabel(this);
        json->setWindowFlags(Qt::Window);
        auto doc = msg.toByteArray();
        //auto tmp = doc.toJson(QJsonDocument::Indented);
        json->setText(doc);
        json->show();
    }
}

void MainView::on_save_snapshot_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Save hierarchy to", QDir::homePath());

    _message_controller->create_dir_structure(path, _message_controller->get_root_topics());
}

