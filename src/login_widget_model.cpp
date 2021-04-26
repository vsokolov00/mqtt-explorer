
#include "login_widget_model.h"

LoginWidgetModel::LoginWidgetModel(QObject *parent) : QAbstractItemModel(parent) { }

QVariant LoginWidgetModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    (void)role;

    return QVariant();
}

QVariant LoginWidgetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    (void)role;

    return QVariant();
}

Qt::ItemFlags LoginWidgetModel::flags(const QModelIndex &index) const
{
    (void)index;

    return Qt::ItemFlags();
}

QModelIndex LoginWidgetModel::index(int row, int column, const QModelIndex &parent) const
{
    (void)row;
    (void)column;
    (void)parent;

    return QModelIndex();
}

QModelIndex LoginWidgetModel::parent(const QModelIndex &index) const
{
    (void)index;

    return QModelIndex();
}

int LoginWidgetModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;

    return 0;
}

int LoginWidgetModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;

    return 0;
}


void LoginWidgetModel::connection_failed(bool connection_exist, const std::string &server_address)
{   
    (void)connection_exist;
    (void)server_address;
    // TODO display red message to the user that login to server adddress failed - try again...
    // if the connection_exist is true, then inform also about this
}

void LoginWidgetModel::connection_failed()
{
    //TODO display red message
}
