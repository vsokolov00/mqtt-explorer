#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>
#include <algorithm>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();

    QVector<TreeItem*> getChildren();

private:
    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
};

#endif // TREEITEM_H
