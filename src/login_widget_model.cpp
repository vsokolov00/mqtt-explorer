
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
