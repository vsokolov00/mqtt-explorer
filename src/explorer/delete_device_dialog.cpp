
/**
 * @file        delete_device_dialog.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the DeleteDeviceDialog class. 
 **/

#include "delete_device_dialog.h"
#include "ui_delete_device_dialog.h"

DeleteDeviceDialog::DeleteDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDeviceDialog)
{
    ui->setupUi(this);

}

DeleteDeviceDialog::~DeleteDeviceDialog()
{
    delete ui;
}

QListWidget* DeleteDeviceDialog::get_device_list()
{
    return ui->device_list;
}

void DeleteDeviceDialog::on_ok_clicked()
{
    std::vector<int> checked;
    for(int i = 0; i < ui->device_list->count(); ++i)
    {
        QListWidgetItem* item = ui->device_list->item(i);
        auto state = item->checkState();
        if (state == Qt::Checked)
        {
            checked.push_back(i);
        }
    }
    emit pass_selected_devices(checked);
    this->accept();
}

void DeleteDeviceDialog::on_cancel_clicked()
{
    this->reject();
}
