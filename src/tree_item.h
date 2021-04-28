#ifndef TREE_ITEM_H
#define TREE_ITEM_H

#include <QVariant>
#include <QVector>
#include <algorithm>


class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendSubtopic(TreeItem *child);

    TreeItem *getSubtopic(int row);
    int subtopicCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *supertopic();

    QVector<TreeItem*> getSubtopics();
    void addMessage(QVariant message, int type, bool our_message); //TODO type numbers changed!! see client.h enum FileType
    int getMessageCnt();

    QString getName();
    QString getPath();
    std::vector<std::tuple<QVariant, QString, bool>> getMessages();

private:
    static const unsigned MSGLIMIT = 10;

    std::vector<QString> types = {"bin", "text", "json", "image"};

    int message_cnt;

    std::vector<std::tuple<QVariant, QString, bool>> msg_history;

    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
    QString full_path;
};

#endif // TREE_ITEM_H
