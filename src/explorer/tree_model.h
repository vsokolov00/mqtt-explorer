
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
     * @brief TODO
     * @param section TODO
     * @param orientation TODO
     * @param role TODO
     * @return TODO
     **/
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * @brief TODO
     * @param index TODO
     * @return TODO
     **/
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief TODO
     * @param row TODO
     * @param columns TODO
     * @param parent TODO
     * @return TODO
     **/
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    
    /**
     * @brief TODO
     * @param index TODO
     * @return TODO
     **/
    QModelIndex parent(const QModelIndex &index) const override;

    /**
     * @brief Gets the number of rows of the model.
     * @param parent TODO
     * @return the number of rows.
     **/
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Gets the number of columns of the model.
     * @param parent TODO
     * @return the number of columns.
     **/
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Gets a message item.
     * @param index TODO
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

