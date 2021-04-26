
#pragma once

#include <QApplication>
#include <QByteArray>

#include "tree_model.h"
#include "client.h"

class MessageDisplayer
{
    private:
        TreeModel *_tree_model;
        QVector<TreeItem *> _topics;
    
        std::vector<std::string> parse_topic_path(std::string path);
        TreeItem* find_topic(std::string name, const QVector<TreeItem*>& topics);
        TreeItem& add_subtopic(TreeItem& supertopic, std::string topic_name, QVariant data);
        void create_hierarchy(TreeItem& supertopic, std::vector<std::string> topics, 
                              bool new_root, QVariant& qv, FileType type);
    
    public:
        MessageDisplayer(TreeModel *tree_model);
        ~MessageDisplayer() = default;

        void display_string(const std::string &topic, const std::string &string_message);
        void display_json(const std::string &topic, const std::string &json_file);
        void display_image(const std::string &topic, const QByteArray &image);
        void display_binary(const std::string &topic, const QByteArray &binary_file);
};
