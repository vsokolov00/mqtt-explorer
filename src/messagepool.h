#ifndef MESSAGEPOOL_H
#define MESSAGEPOOL_H

#include <QMainWindow>
#include <QFileSystemModel>

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

private:
    Ui::MessagePool *ui;
};

#endif // MESSAGEPOOL_H
