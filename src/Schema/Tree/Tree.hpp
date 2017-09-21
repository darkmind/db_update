// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Node.hpp"

#include <memory>
#include <string>
#include <vector>

class Tree
{
public:

    Tree();

    std::shared_ptr<Node> get_root() const;

    std::shared_ptr<Node> find_node( const std::string& name ) const;
    std::shared_ptr<Node> find_node( const std::string& name, const std::shared_ptr<Node> root_node ) const;

    void dump_tree() const;
    void dump_tree( const size_t& counter, const std::shared_ptr<Node> node ) const;

private:

    std::shared_ptr<Node> root;

    std::size_t counter;
};

