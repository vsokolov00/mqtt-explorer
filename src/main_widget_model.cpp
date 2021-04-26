
#include "main_widget_model.h"

MainWidgetModel::MainWidgetModel(QObject *parent) : QAbstractItemModel(parent) {}

QVariant MainWidgetModel::data(const QModelIndex &index, int role) const
{
    (void)index;
    (void)role;

    return QVariant();
}

QVariant MainWidgetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    (void)section;
    (void)orientation;
    (void)role;

    return QVariant();
}

Qt::ItemFlags MainWidgetModel::flags(const QModelIndex &index) const
{
    (void)index;

    return Qt::ItemFlags();
}

QModelIndex MainWidgetModel::index(int row, int column, const QModelIndex &parent) const
{
    (void)row;
    (void)column;
    (void)parent;

    return QModelIndex();
}

QModelIndex MainWidgetModel::parent(const QModelIndex &index) const
{
    (void)index;

    return QModelIndex();
}

int MainWidgetModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;

    return 0;
}

int MainWidgetModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;

    return 0;
}


void MainWidgetModel::publish_success(int message_id)
{
    (void)message_id;
    // TODO register the ID and wait for delivery complete
}

void MainWidgetModel::publish_failure(int message_id)
{
    (void)message_id;
    //TODO inform the user
}

void MainWidgetModel::delivery_complete(int message_id)
{
    (void)message_id;
    //TODO find the ID and mark the message as delivered
}


void MainWidgetModel::subscription_success(const std::string &topic)
{
    (void)topic;
    // TODO display a message (green for X seconds) with the subscribed topic
}

void MainWidgetModel::subscription_failure(const std::string &topic)
{
    (void)topic;
    // TODO display a message (red for X seconds) with the subscribed topic
}

void MainWidgetModel::unsubscription_success(const std::string &topic)
{
    (void)topic;
    // TODO display a message (green for X seconds) with the unsubscribed topic
}

void MainWidgetModel::unsubscription_failure(const std::string &topic)
{
    (void)topic;
    // TODO display a message (red for X seconds) with the unsubscribed topic
}
