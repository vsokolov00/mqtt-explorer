
#pragma once

#include <QAbstractItemModel>

class MainWidgetModel : public QAbstractItemModel
{
    Q_OBJECT

    public:
        MainWidgetModel(QObject *parent);
        ~MainWidgetModel() = default;

        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        void publish_success(int message_id);
        void publish_failure(int message_id);

        void subscription_success(const std::string &topic);
        void subscription_failure(const std::string &topic);

        void unsubscription_success(const std::string &topic);
        void unsubscription_failure(const std::string &topic);

        void delivery_complete(int message_id);

        void connection_lost();
        void reconnect_failed(bool connection_exist, const std::string &server_address);
        void reconnect_failed();
};
