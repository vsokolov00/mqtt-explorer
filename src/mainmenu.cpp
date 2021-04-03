#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <mqtt/async_client.h>
#include <mqtt/topic.h>

MainMenu::MainMenu(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::display_topics(mqtt::async_client &client)
{
    //mqtt::topic topic = mqtt::topic(client, "$SYS/broker/heap", 1);
    //auto subOpts = mqtt::subscribe_options(true);
    try {
       //topic.subscribe(subOpts)->wait();
       std::cout << "OK" << std::endl;
    }  catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << " ["
                    << exc.get_reason_code() << "]" << std::endl;
        std::cout << "FAIL" << std::endl;
        return;
    }
}
