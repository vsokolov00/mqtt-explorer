#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectBroker_clicked()
{
    const std::string protocol = ui->protocol->text().toStdString();
    const std::string  host = ui->host->text().toStdString();
    const std::string  port = ui->port->text().toStdString();
    const std::string  user = ui->user->text().toStdString();
    const std::string  password = ui->password->text().toStdString();

    const std::string address = protocol + host + port;

    mqtt::async_client client = mqtt::async_client(address, user);
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(std::chrono::seconds(20));
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to the server at " << host << std::endl;
        client.connect(connOpts);
        std::cout << "Success. " << host << std::endl;
    } catch(const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << " ["
                    << exc.get_reason_code() << "]" << std::endl;
                throw exc;
    }

    //opens new window with topics and messages
    hide();
    main_menu = new MainMenu(this);
    main_menu->show();
    main_menu->display_topics(client);
}
