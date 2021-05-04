#include "dashboard_view.h"
#include "ui_dashboard.h"

DashboardView::DashboardView(DashboardController *dashboard_controller) :
    QMainWindow(nullptr), _ui(new Ui::Dashboard)
{
    _ui->setupUi(this);
}

DashboardView::~DashboardView()
{
    delete _ui;
}
