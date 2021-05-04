
#pragma once

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "dashboard_controller.h"
#include "flowlayout.h"
#include "log.h"

class DashboardView : public QWidget
{
    Q_OBJECT

private:
    FlowLayout* _flow_layout;
    DashboardController* _dashboard_controller;

private slots:
    void on_add_device_clicked();

public:
    explicit DashboardView(DashboardController *dashboard_controller);
    ~DashboardView();

};
