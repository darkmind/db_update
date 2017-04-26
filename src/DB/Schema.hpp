// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Node.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

class Schema
{

public:
    Schema();

    void print_schema();

    void add_table_columns( const std::shared_ptr<Node> table );

    void add_table_info( const std::shared_ptr<Node> table );

    std::vector<std::string> get_tables_list();

    std::shared_ptr<Node> get_schema();

private:
    std::shared_ptr<Node> schema;
};

