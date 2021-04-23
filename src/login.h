#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui { class Login; }

class Login: public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_connect_clicked();

signals:
    void login_successfull();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
