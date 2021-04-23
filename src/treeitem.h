#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>
#include <algorithm>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr, std::string path = "");
    ~TreeItem();

    void appendSubtopic(TreeItem *child);

    TreeItem *getSubtopic(int row);
    int subtopicCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *supertopic();

    QVector<TreeItem*> getSubtopics();
    void addMessage(QVariant msg);
    int getMessageCnt();

    QString getName();
    QVector<QVariant> getMessages();
    QString getPath();

private:
    const int MSGLIMIT = 20;
    int message_cnt;
    QVector<QVariant> msg_history;

    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
    QString full_path;
};

#endif // TREEITEM_H
