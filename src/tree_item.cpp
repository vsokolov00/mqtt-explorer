#include "tree_item.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : m_itemData(data), m_parentItem(parent)
{
    message_cnt = 0;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendSubtopic(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::getSubtopic(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::subtopicCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 2;
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
    {
        return QVariant();
    }
    else if (column == 1)
        {
            QString raw_data = m_itemData.at(1).toString();
            if (!raw_data.toStdString().empty())
            {
                if (raw_data.size() < 40)
                {
                    return QVariant(raw_data);
                }
                raw_data = raw_data.left(40);
                raw_data += "...";
                return QVariant(raw_data);
            }
        }
    return m_itemData.at(column);
}

TreeItem *TreeItem::supertopic()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

QVector<TreeItem*> TreeItem::getSubtopics()
{
    return m_childItems;
}

int TreeItem::getMessageCnt()
{
    return message_cnt;
}

void TreeItem::addMessage(QVariant message, int type, bool our_message) //TODO check types
{
    (void)our_message;//TODO remove, if true - mark the message as send by us, otherwise mark it as recieved from the borker
    this->message_cnt++;
    this->m_itemData[1] = message;
    if (msg_history.size() > MSGLIMIT)
    {
        msg_history.erase(msg_history.begin());
    }
    this->msg_history.push_back(std::make_tuple(message, types[type]));
}

QString TreeItem::getName()
{
    return this->m_itemData[0].toString();
}

std::vector<std::tuple<QVariant, QString>> TreeItem::getMessages()
{
    return msg_history;
}

QString TreeItem::getPath()
{
    return this->full_path;
}


