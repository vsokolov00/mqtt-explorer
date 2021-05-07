
/**
 * @file        tree_item.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Implementation of constructors, destructors and functions of the TreeItem class.
 **/

#include "tree_item.h"

const unsigned TreeItem::MSGLIMIT = 10;
const QString TreeItem::TYPES[4] = {"binary", "text", "json", "image"};

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

void TreeItem::addMessage(QVariant message, unsigned short type, bool our_message)
{
    this->message_cnt++;
    this->m_itemData[1] = message;
    if (msg_history.size() > MSGLIMIT)
    {
        msg_history.erase(msg_history.begin());
    }
    this->msg_history.push_back(std::make_tuple(message, TYPES[(type >> 1) > 2 ? 3 : type >> 1], our_message));
}

QString TreeItem::getName()
{
    return this->m_itemData[0].toString();
}

std::vector<std::tuple<QVariant, QString, bool>> TreeItem::getMessages()
{
    return msg_history;
}

QString TreeItem::getPath()
{
    return this->full_path;
}


