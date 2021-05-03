
#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QBrush>

#include <map>

#include "tree_item.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    TreeItem *_rootItem;

public:
    explicit TreeModel(QObject *parent);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    TreeItem *getItem(const QModelIndex &index) const;
    TreeItem& getRoot();

    QString getPath(TreeItem& t);
};

