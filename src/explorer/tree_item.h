
/**
 * @file        tree_item.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class, which represents one message in tree structure displayed 
 *              in the application.
 **/

#pragma once

#include <QVariant>
#include <QVector>
#include <algorithm>

#include "../client/client.h"
#include "../client/listener.h"

class TreeItem
{
    private:
        static const unsigned MSGLIMIT;
        static const QString TYPES[4];

    private:
        int message_cnt;

        std::vector<std::tuple<QVariant, QString, bool>> msg_history;

        QVector<TreeItem*> m_childItems;
        QVector<QVariant> m_itemData;
        TreeItem *m_parentItem;
        QString full_path;

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
        void addMessage(QVariant message, unsigned short type, bool our_message); //TODO type numbers changed!! see client.h enum FileType
        int getMessageCnt();

        QString getName();
        QString getPath();
        std::vector<std::tuple<QVariant, QString, bool>> getMessages();
};

