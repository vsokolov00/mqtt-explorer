#ifndef DELETE_DEVICE_DIALOG_H
#define DELETE_DEVICE_DIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class DeleteDeviceDialog;
}

class DeleteDeviceDialog : public QDialog
{
    Q_OBJECT

signals:
    void pass_selected_devices(std::vector<int>);

public:
    explicit DeleteDeviceDialog(QWidget *parent = nullptr);
    ~DeleteDeviceDialog();

    QListWidget* get_device_list();

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::DeleteDeviceDialog *ui;
};

#endif // DELETE_DEVICE_DIALOG_H
