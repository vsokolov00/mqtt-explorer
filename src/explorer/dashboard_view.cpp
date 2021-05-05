#include "dashboard_view.h"
#include "ui_dashboard.h"

DashboardView::DashboardView(DashboardController *dashboard_controller, FlowLayout *flow_layout) :
    _dashboard_controller(dashboard_controller), _flow_layout(flow_layout)
{
    QVBoxLayout *central_layout = new QVBoxLayout();
    QPushButton *add_device = new QPushButton();
    add_device->setText("Add device");
    QObject::connect(add_device, &QPushButton::clicked, this, &DashboardView::on_add_device_clicked);

    _dialog = new NewDeviceDialog(this);

    central_layout->addWidget(add_device);
    central_layout->addLayout(_flow_layout);
    setLayout(central_layout);

    this->setWindowTitle("Dashboard");
    this->resize(800, 400);

    connect(_dialog, SIGNAL(new_device_added(QString,QString,uint)), this, SLOT(add_device(QString,QString,uint)));
}

DashboardView::~DashboardView()
{
    delete _dialog;
}

void DashboardView::on_add_device_clicked()
{
    int result_code = _dialog->exec();

    if (result_code == QDialog::Accepted)
    {
    }
    else if (result_code == QDialog::Rejected)
    {
    }
}

void DashboardView::add_device(QString name, QString topic, unsigned device_type)
{
    auto device = new DeviceWidget(this, static_cast<DeviceType>(device_type), name, topic);
    _flow_layout->addWidget(device);
    _dashboard_controller->add_device(device);
}

