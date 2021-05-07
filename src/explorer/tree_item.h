
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

/**
 * @brief Node of a data structure used for storing messgaes
 **/
class TreeItem
{
    private:
        static const unsigned MSGLIMIT;         ///< the maximum number of stored messages at one topic
        static const QString TYPES[4];          ///< types of messages

    private:
        int message_cnt;               ///< curent count of messages in a given node

        /**
         * @brief message history of a given node with data, type and true if message was send by us, otherwise false.
         **/
        std::vector<std::tuple<QVariant, QString, bool>> msg_history;

        QVector<TreeItem*> m_childItems;        ///< children nodes
        QVector<QVariant> m_itemData;           ///< message data
        TreeItem *m_parentItem;                 ///< parent node
        QString full_path;                      ///< topic path to this node from its root node

    public:
        explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
        ~TreeItem();
        
        /**
         * @brief Adds a new subtopic to the current node.
         * @param child the added subtopic.
         **/
        void appendSubtopic(TreeItem *child);

        /**
         * @brief Gets a subtopic of the current node.
         * @param row the Nth children on the node.
         **/
        TreeItem *getSubtopic(int row);

        /**
         * @brief Gets a number of children/subtopic of the current node.
         * @return the number of subtopics.
         **/
        int subtopicCount() const;

        /**
         * @brief Gets a number of columns.
         * @return the number of columns.
         **/
        int columnCount() const;

        /**
         * @brief Gets data of a column.
         * @return the column of which data are returned.
         **/
        QVariant data(int column) const;

        /**
         * @brief Gets a number of rows.
         * @return the number of rows.
         **/
        int row() const;

        /**
         * @brief Gets a parent topic.
         * @return the parent topic.
         **/
        TreeItem *supertopic();

        /**
         * @brief Gets children topics.
         * @return the children topics.
         **/
        QVector<TreeItem*> getSubtopics();

        /**
         * @brief Adds a new message to the node.
         * @param message the newly added message.
         * @param type the type of the added message.
         * @param our_message true when the message was send by our application, otherwise false.
         **/
        void addMessage(QVariant message, unsigned short type, bool our_message);

        /**
         * @brief Gets a number of messages on the node.
         * @return the number of messages.
         **/
        int getMessageCnt();

        /**
         * @brief Gets a name of the nodes topic.
         * @return the topic name.
         **/
        QString getName();

        /**
         * @brief Gets a topic path to the node.
         * @return the topic path.
         **/
        QString getPath();

        /**
         * @brief Gets a message of the current node.
         * @return 1: the data of the message
         *         2: the topic path of the message
         *         3: true when the message was send by our application, otherwise false.
         **/
        std::vector<std::tuple<QVariant, QString, bool>> getMessages();
};

