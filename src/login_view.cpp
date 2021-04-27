#include "login_view.h"
#include "ui_login.h"
#include "program.h"

LoginView::LoginView(LoginWidgetModel *login_widget_model, ConnectionController *connection_cotroller)
      : QMainWindow(nullptr), _ui(new Ui::Login), _login_widget_model(login_widget_model), 
        _connection_controller(connection_cotroller)
{
    _ui->setupUi(this);

    _ui->protocol->addItem("tcp://");
    _ui->protocol->addItem("mqtt://");
    _ui->host->setText("test.mosquitto.org");
    _ui->port->setText("1883");
    _ui->user->setText("");
    _ui->password->setText("");
    _ui->clean_session->setChecked(true);
    _ui->connection_id->setText("id_123_ab");
}

LoginView::~LoginView()
{
    delete _ui;
}

void LoginView::on_connect_clicked()
{   
    Log::log("On connected clicked.");
    std::string server_address = (_ui->protocol->currentIndex() == 0 ? "tcp://" : "") +
                                  _ui->host->text().toStdString() + ":" + _ui->port->text().toStdString();


    //TODO start login countdown - loading cirle
//    QLabel *lbl =_ui->loading;
//    lbl->setFixedSize(QSize(100,100));
//    QMovie *movie = new QMovie(":gifs/loader.gif");
//    lbl->setMovie(movie);
//    lbl->show();
//    movie->start();

    Log::log("Calling connect.");
    _connection_controller->connect(server_address, _ui->connection_id->text().toStdString(), _ui->user->text().toStdString(),
                                    _ui->password->text().toStdString(), _ui->clean_session->checkState());
    
    //TODO remove just a demonstration
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    _connection_controller->disconnect();
}

