
#pragma once

#include <QAbstractItemModel>

class LoginWidgetModel : public QAbstractItemModel
{
    Q_OBJECT

    public:
        LoginWidgetModel(QObject *parent);
        ~LoginWidgetModel() = default;

        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        void connection_failed(bool connection_exist, const std::string &server_address);
        void connection_failed();
};
