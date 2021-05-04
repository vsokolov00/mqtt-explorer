#pragma once

#include <QMainWindow>
#include "dashboard_controller.h"

namespace Ui { class Dashboard; }

class DashboardView : public QMainWindow
{
    Q_OBJECT

public:
    explicit DashboardView(DashboardController *dashboard_controller);
    ~DashboardView();

private:
    Ui::Dashboard *_ui;
};

