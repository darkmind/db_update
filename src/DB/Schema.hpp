// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include <Types.hpp>
#include <unordered_map>
#include <memory>
#include <string>

class Schema
{

public:
    Schema();

    void print_schema();

    void add_table_columns( const std::string& table_name, const table_property& columns );

    void add_table_info( const std::string& table_name, const table_property& table_info );

    std::vector<std::string> get_tables_list();

    std::shared_ptr<schema_type> get_schema();

private:
    std::shared_ptr<schema_type> schema;
};
