
/**
 * @file        tree_model.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the TreeModel class.
 **/

#include "tree_model.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    _rootItem = new TreeItem({tr("Topic"), tr("Last message")});
}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return _rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto given_item = getItem(index);
    auto msgs = given_item->getMessages();

    if (role == Qt::BackgroundRole && !msgs.empty())
    {
        auto last_msg = msgs.back();
        bool last_is_our = std::get<2>(last_msg);
        if (last_is_our)
        {
            return QBrush(Qt::lightGray);
        }
    }
    else if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsSelectable  | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->getSubtopic(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->supertopic();

    if (parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->subtopicCount();
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) 
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem;
}

TreeItem& TreeModel::getRoot()
{
    return *this->_rootItem;
}

QString TreeModel::getPath(TreeItem& t)
{
    QString pathStr;
    std::vector<QString> path;

    path.push_back(t.getName());
    TreeItem* tmp = &t;


    while(tmp->supertopic() != _rootItem)
    {
        path.push_back(tmp->supertopic()->getName());
        tmp = tmp->supertopic();
    }

    std::reverse(path.begin(), path.end());
    for (auto &t : path)
    {
        pathStr += t;
        if (t != path[path.size() - 1])
            pathStr += "/";
    }
    return pathStr;
}
