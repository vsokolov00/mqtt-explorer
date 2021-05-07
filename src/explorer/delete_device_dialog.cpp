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
