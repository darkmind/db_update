// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include <memory>
#include <utility>
#include <string>
#include <unordered_map>
#include <vector>

class Node
{
public:

    explicit Node( const std::string& node_name );
    ~Node();

    std::string get_name() const;

    void set_parent( const std::shared_ptr<Node> node );
    std::shared_ptr<Node> get_parent() const;

    void add_child( const std::shared_ptr<Node> node );
    std::shared_ptr<Node> get_child( const std::string& name ) const;
    std::vector<std::shared_ptr<Node>> get_children() const;

    void add_data( const std::string& key, const std::string& value );
    void set_data( const std::unordered_map<std::string, std::string>& in_data );
    std::unordered_map<std::string, std::string> get_data() const;

    void set_type( const std::string& i_type );
    std::string get_type() const;

    bool has_children() const;

private:

    std::string node_name;

    std::string type;

    std::weak_ptr<Node> parent;

    std::vector<std::shared_ptr<Node>> children;

    std::unordered_map<std::string, std::string> data;
};

