#ifndef NEW_DEVICE_DIALOG_H
#define NEW_DEVICE_DIALOG_H

#include <QDialog>

namespace Ui {
class NewDeviceDialog;
}

class NewDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDeviceDialog(QWidget *parent = nullptr);
    ~NewDeviceDialog();
signals:
    void new_device_added(QString name, QString topic, unsigned device_type);

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::NewDeviceDialog *ui;
};

#endif // NEW_DEVICE_DIALOG_H
