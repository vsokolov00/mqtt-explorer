
#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "new_device_dialog.h"
#include "dashboard_controller.h"
#include "flowlayout.h"
#include "log.h"

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
    explicit DashboardView(DashboardController *dashboard_controller);
    ~DashboardView();

};
