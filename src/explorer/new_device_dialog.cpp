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
