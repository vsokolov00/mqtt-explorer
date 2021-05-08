
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
    _add_device->setText("Add Device");
    _delete_device = new QPushButton();
    _delete_device->setText("Delete Device");
    QObject::connect(_add_device, &QPushButton::clicked, this, &DashboardView::on_add_device_clicked);
    QObject::connect(_delete_device, &QPushButton::clicked, this, &DashboardView::on_delete_device_clicked);

    _add_dialog = new NewDeviceDialog(this);
    _delete_dialog = new DeleteDeviceDialog(this);

    _central_layout->addWidget(_add_device);
    _central_layout->addWidget(_delete_device);
    _central_layout->addLayout(_flow_layout);
    setLayout(_central_layout);

    this->setWindowTitle("Dashboard");
    this->resize(1390, 700);

    connect(_add_dialog, SIGNAL(new_device_added(QString,QString,uint)), this, SLOT(add_device(QString,QString,uint)));
    connect(_delete_dialog, SIGNAL(pass_selected_devices(std::vector<int>)), this, SLOT(delete_devices(std::vector<int>)));
}

DashboardView::~DashboardView()
{
    delete _central_layout;
    delete _add_device;
    delete _delete_device;
    delete _add_dialog;
    delete _delete_dialog;
}

void DashboardView::on_add_device_clicked()
{
    int result_code = _add_dialog->exec();

    if (result_code == QDialog::Accepted)
    {
    }
    else if (result_code == QDialog::Rejected)
    {
    }
}

void DashboardView::on_delete_device_clicked()
{
    auto list = _delete_dialog->get_device_list();
    list->clear();

    for (auto& topic : _dashboard_controller->get_topics())
    {
        auto name = _dashboard_controller->topic_to_device[topic]->get_name();
        list->addItem(QString::fromStdString(name));
    }
    for(int i = 0; i < list->count(); ++i)
    {
        QListWidgetItem* item = list->item(i);
        item->setCheckState(Qt::Unchecked);
    }
    int result_code = _delete_dialog->exec();

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

void DashboardView::delete_devices(std::vector<int> devices)
{
    _dashboard_controller->delete_devices(devices);
    _flow_layout->delete_item(devices);
    _flow_layout->update();
}

