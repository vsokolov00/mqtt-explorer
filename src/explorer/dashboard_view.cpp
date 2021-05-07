
/**
 * @file        dashboard_view.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the DasboardView class.
 **/

#include "dashboard_view.h"
#include "ui_dashboard.h"


DashboardView::DashboardView(DashboardController *dashboard_controller, FlowLayout *flow_layout) :
    _dashboard_controller(dashboard_controller), _flow_layout(flow_layout)
{
    _central_layout = new QVBoxLayout();
    _add_device = new QPushButton();
    _add_device->setText("Add device");
    QObject::connect(_add_device, &QPushButton::clicked, this, &DashboardView::on_add_device_clicked);

    _dialog = new NewDeviceDialog(this);

    _central_layout->addWidget(_add_device);
    _central_layout->addLayout(_flow_layout);
    setLayout(_central_layout);

    this->setWindowTitle("Dashboard");
    this->resize(1390, 680);

    connect(_dialog, SIGNAL(new_device_added(QString,QString,uint)), this, SLOT(add_device(QString,QString,uint)));
}

DashboardView::~DashboardView()
{
    delete _central_layout;
    delete _add_device;
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

