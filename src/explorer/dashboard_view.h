
#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "new_device_dialog.h"
#include "flowlayout.h"
#include "log.h"
#include "dashboard_controller.h"

class DashboardController;

class DashboardView : public QWidget
{
    Q_OBJECT

private:
    FlowLayout* _flow_layout;
    DashboardController* _dashboard_controller;
    NewDeviceDialog* _dialog;

private slots:
    void on_add_device_clicked();
    void add_device(QString name, QString topic, unsigned device_type);

public:
    DashboardView(DashboardController *dashboard_controller, FlowLayout *flow_layout);
    ~DashboardView();

};
