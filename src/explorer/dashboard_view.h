#pragma once

#include <QMainWindow>
#include <QPushButton>
#include "dashboard_controller.h"
#include "flowlayout.h"


class DashboardView : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardView(DashboardController *dashboard_controller);
    ~DashboardView();
};

