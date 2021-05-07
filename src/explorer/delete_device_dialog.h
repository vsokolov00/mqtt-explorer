#ifndef DELETE_DEVICE_DIALOG_H
#define DELETE_DEVICE_DIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class DeleteDeviceDialog;
}

/**
 * @brief Displays a window where a new devices from the dashboard can be deleted.
 **/
class DeleteDeviceDialog : public QDialog
{
    Q_OBJECT
/**
  * Signal that is emited when user selected devices to delete
  **/
signals:
    void pass_selected_devices(std::vector<int>);

public:
    explicit DeleteDeviceDialog(QWidget *parent = nullptr);
    ~DeleteDeviceDialog();

    /**
     * @brief Returns list widget of the devices
     */
    QListWidget* get_device_list();

private slots:
    /**
     * @brief on_ok_clicked Slot is triggered when user presses ok in the dialog
     */
    void on_ok_clicked();

    /**
     * @brief on_cancel_clicked Slot is triggered when user presses cancel in the dialog
     */
    void on_cancel_clicked();

private:
    Ui::DeleteDeviceDialog *ui;
};

#endif // DELETE_DEVICE_DIALOG_H
