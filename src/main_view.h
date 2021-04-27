
#pragma once

#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QStringList>
#include <QBuffer>
#include <QString>

#include "client.h"
#include "log.h"

#include "tree_model.h"
#include "main_widget_model.h"

#include "connection_controller.h"
#include "message_controller.h"
#include "subscription_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// TODO rename to MainView, the file to main_view.h
class MainView : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_publish_clicked();
    void on_subscribe_clicked();
    void on_unsubscribe_clicked();
    void on_chooseFile_clicked();
    void on_clear_clicked();

    //TODO
    void on_disconnect_clicked();
    void on_reconnect_clicked();
    void on_exit_clicked();

private:
    Ui::MainWindow *_ui = nullptr;

    TreeModel *_tree_model = nullptr;
    MainWidgetModel *_main_widget_model = nullptr;

    ConnectionController *_connection_controller = nullptr;
    MessageController *_message_controller = nullptr;
    SubscriptionController *_subscription_controller = nullptr;

public:
    MainView(TreeModel *tree_model, MainWidgetModel *main_widget_model, ConnectionController *connection_controller,
               MessageController *message_controller, SubscriptionController *subscription_controller);
    ~MainView();

    void item_selection();
    void display();
};
