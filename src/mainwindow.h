#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QStringList>

#include "messagecontroller.h"
#include "subscriptioncontroller.h"
#include "mqttreemodel.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_models();
    void init_controllers();
    void login();

    void show_main_window();

    void item_selection(); 

private slots:
    void on_publish_clicked();
    void on_subscribe_clicked();

    void on_unsubscribe_clicked();

    void on_chooseFile_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
    TreeModel* main_model;

    MessageController* message_controller;
    ConnectionController* conn_controller;
    SubscriptionController* sub_constroller;
};

#endif // MAINWINDOW_H
