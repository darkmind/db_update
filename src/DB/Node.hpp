// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <memory>
#include <utility>
#include <string>
#include <unordered_map>
#include <map>

class Node
{
public:
    explicit Node( const std::string& node_name );
    ~Node();

    std::string get_name();

    void set_parent( const std::shared_ptr<Node> node );
    std::shared_ptr<Node> get_parent();

    void add_child( const std::shared_ptr<Node> node );
    std::shared_ptr<Node> get_child( const std::string& name );
    std::unordered_map<std::string, std::shared_ptr<Node>> get_children();

    void add_data( const std::string& key, const std::string& value );
    std::map<std::string, std::string> get_data();

    bool has_children();

private:
    std::string node_name;

    std::weak_ptr<Node> parent;

    std::unordered_map<std::string, std::shared_ptr<Node>> children;

    std::map<std::string, std::string> data;
};

