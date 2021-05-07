
/**
 * @file        tree_model.h                                 
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Declaration of a class representing a tree model used to display messages
 *              in the application.
 **/

#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QBrush>

#include <map>

#include "tree_item.h"

/**
 * @brief The main data model of the application, stores the message tree.
 **/
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
    TreeItem *_rootItem;            ///< root of the message tree

public:
    explicit TreeModel(QObject *parent);
    ~TreeModel();

    /**
     * @brief Gets message data of a node based on a index.
     * @param index the index of the data.
     * @param role determines how the data are displayed.
     * @return the message data.
     **/
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Retrieves tree view root data
     * @param section of the tree view
     * @param orientation of the tree view header
     * @param role of the header
     * @return root item data
     **/
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns item flags for the given index
     * @param index of tree view item
     * @return item flags
     **/
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief Retrives the index of an element according to the row, column and parent (supertopic) item
     * of that item
     * @param row of the item
     * @param columns of the item
     * @param parent of the item
     * @return QModelIndex object of that item
     **/
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    
    /**
     * @brief Retrieves the index to the parent item (supertopic) of the given item
     * @param index to item
     * @return QModelIndex object of the parent item
     **/
    QModelIndex parent(const QModelIndex &index) const override;

    /**
     * @brief Gets the number of rows of the model.
     * @param parent tree view item index to be examined
     * @return the number of rows (subtopics).
     **/
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Gets the number of columns of the model.
     * @param parent tree view item index to be examined
     * @return the number of columns.
     **/
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Gets a message item.
     * @param index to the tree view item
     * @return the message item.
     **/
    TreeItem *getItem(const QModelIndex &index) const;

    /**
     * @brief Gets the root node of the tree strusture.
     * @return the root node.
     **/
    TreeItem& getRoot();

    /**
     * @brief Gets a topic path to a node.
     * @param t the node to be examined.
     * @return the topic path.
     **/
    QString getPath(TreeItem& t);
};

