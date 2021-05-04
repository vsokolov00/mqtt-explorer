#include "dashboard_view.h"
#include "ui_dashboard.h"

DashboardView::DashboardView(DashboardController *dashboard_controller)
{
    FlowLayout *flowLayout = new FlowLayout;

    flowLayout->addWidget(new QPushButton(tr("Short")));
    flowLayout->addWidget(new QPushButton(tr("Longer")));
    flowLayout->addWidget(new QPushButton(tr("Different text")));
    flowLayout->addWidget(new QPushButton(tr("More text")));
    flowLayout->addWidget(new QPushButton(tr("Even longer button text")));
    setLayout(flowLayout);
}

DashboardView::~DashboardView()
{

}
