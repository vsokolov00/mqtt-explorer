#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "mqttreemodel.h"
#include "log.h"
#include "message_publisher.h"
#include "message_displayer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_publish_clicked();
    void on_subscribe_clicked();
    void on_unsubscribe_clicked();
    void on_chooseFile_clicked();
    void on_clear_clicked();

private:
    Ui::MainWindow *_ui = nullptr;
    TreeModel* _tree_model = nullptr;
    Client *_client = nullptr;
    MessagePublisher *_message_publisher = nullptr;
    MessageDisplayer *_message_displayer = nullptr;

public:
    MainWindow();
    ~MainWindow();
    
    void register_client(Client *client);
    MessageDisplayer *get_message_displayer() const;

    void item_selection();

    void subscription_success(const std::string &topic);
    void subscription_failure(const std::string &topic);

    void unsubscription_success(const std::string &topic);
    void unsubscription_failure(const std::string &topic);

    void connection_lost();
};

#endif // MAINWINDOW_H
