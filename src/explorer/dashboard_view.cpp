#include "dashboard_view.h"
#include "ui_dashboard.h"

DashboardView::DashboardView(DashboardController *dashboard_controller) :
    _dashboard_controller(dashboard_controller)
{
    QVBoxLayout *central_layout = new QVBoxLayout();
    QPushButton *add_device = new QPushButton();
    add_device->setText("Add device");
    QObject::connect(add_device, &QPushButton::clicked, this, &DashboardView::on_add_device_clicked);

    _flow_layout = new FlowLayout;

    central_layout->addWidget(add_device);
    central_layout->addLayout(_flow_layout);
    setLayout(central_layout);
}

DashboardView::~DashboardView()
{

}

void DashboardView::on_add_device_clicked()
{
//    QDialog *dialog = new QDialog();
//    dialog->setWindowTitle("New device");
//    dialog->show();

    _flow_layout->addWidget(new DeviceWidget(this, DeviceType::LIGHT, "Living room", "home/lights/living room"));

//    _dashboard_controller->add_device();
}
