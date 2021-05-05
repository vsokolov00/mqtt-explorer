
/**
 * @file        new_device_dialog.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Authors:     Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the NewDeviceDialog class.
 **/

#include "new_device_dialog.h"
#include "ui_new_device_dialog.h"

NewDeviceDialog::NewDeviceDialog(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::NewDeviceDialog)
{
    _ui->setupUi(this);
}

NewDeviceDialog::~NewDeviceDialog()
{
    delete _ui;
}

void NewDeviceDialog::on_ok_clicked()
{
    emit new_device_added(_ui->device_name->text(), _ui->device_topic->text(), _ui->device_type->currentIndex() + 1);
    this->accept();
}

void NewDeviceDialog::on_cancel_clicked()
{
    this->reject();
}
