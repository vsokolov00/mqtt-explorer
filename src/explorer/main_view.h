
#pragma once

#include <iostream>

#include <QApplication>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>
#include <QStringList>
#include <QTextStream>
#include <QBuffer>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>

#include "../client/client.h"
#include "../client/listener.h"
#include "log.h"
#include "popup.h"

#include "tree_model.h"
#include "dashboard_view.h"

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

    void on_save_snapshot_clicked();

    void on_dashboard_clicked();
signals:
    void dashboard_opened();

private:
    Ui::MainWindow *_ui = nullptr;
    DashboardView *_dashboard_window = nullptr;\

    TreeModel *_tree_model = nullptr;

    ConnectionController *_connection_controller = nullptr;
    MessageController *_message_controller = nullptr;
    SubscriptionController *_subscription_controller = nullptr;

    PopUp* pop_up;
    void show_popup();

public:
    MainView(TreeModel *tree_model, ConnectionController *connection_controller,
               MessageController *message_controller, SubscriptionController *subscription_controller, DashboardView *dashboard_window);
    ~MainView();

    void item_selection();
    void display();
public slots:
    void publish_success_popup_set();
    void publish_failure_popup_set();
    void subscribe_failure_popup_set(QString s);
    void subscribe_success_popup_set(QString s);
    void unsubscribe_failure_popup_set(QString s);
    void unsubscribe_success_popup_set(QString s);
    void connection_lost_dialog();
    void reconnection_failed_dialog();
    void connection_failure_popup_set(QString, bool);
    void connection_failure_popup_set();
    void connection_success_popup_set();
    void display_full_message(QListWidgetItem*);
};
