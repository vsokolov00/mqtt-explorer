#ifndef MESSAGEPOOL_H
#define MESSAGEPOOL_H

#include <QMainWindow>
#include <QFileSystemModel>

#include "topicsengine.h"
#include "mqttreemodel.h"

namespace Ui {
class MessagePool;
}

class MessagePool : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessagePool(QWidget *parent = nullptr);
    ~MessagePool();
    void display_message_tree();
    void item_selection();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MessagePool *ui;
    TreeModel* model;
    TopicsEngine* engine;
};

#endif // MESSAGEPOOL_H
