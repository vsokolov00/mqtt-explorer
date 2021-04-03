#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <mqtt/async_client.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void set_topic();
    void display_topics(mqtt::async_client &client);

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
