#include "new_device_dialog.h"
#include "ui_new_device_dialog.h"

NewDeviceDialog::NewDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDeviceDialog)
{
    ui->setupUi(this);
}

NewDeviceDialog::~NewDeviceDialog()
{
    delete ui;
}

void NewDeviceDialog::on_ok_clicked()
{
    emit new_device_added(ui->device_name->text(), ui->device_topic->text(), ui->device_type->currentIndex() + 1);
    this->accept();
}

void NewDeviceDialog::on_cancel_clicked()
{
    this->reject();
}
