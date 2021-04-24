#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "connectioncontroller.h"

namespace Ui { class Login; }

class Login: public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr, ConnectionController *cc = nullptr);
    ~Login();

private slots:
    void on_connect_clicked();

signals:
    void login_successfull();

private:
    Ui::Login *ui;
    ConnectionController* cc;
};
#endif // LOGIN_H
