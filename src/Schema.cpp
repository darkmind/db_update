// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include "Schema.hpp"
#include "Schema/DB/IO.hpp"
#include "Schema/File/XML_Handler.hpp"
#include "Schema/Tree/Tree.hpp"
#include "Schema/Tree/Node.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

Schema::Schema( const unordered_map<string, string>& options, const int& location )
{
    if ( location == 1 ) {
        io = unique_ptr<Reader>( new IO(options) );
    }
    else if ( location == 2 ) {
        io = unique_ptr<Reader>( new XML_Handler(options) );
    }
}

mysql_rows Schema::execute_direct_sql ( const std::string& statement ) const
{
    return io->execute(statement);
}

void Schema::get_table() const
{}
void Schema::get_table( const std::string& table_name ) const
{}

void Schema::get_column( const std::string& table_name ) const
{}
void Schema::get_column( const std::string& table_name, const std::string& column_name ) const
{}

void Schema::get_index( const std::string& table_name ) const
{}
void Schema::get_index( const std::string& table_name, const std::string& index_name ) const
{}

void Schema::add_table( const std::shared_ptr<Node> table ) const
{}

void Schema::add_column( const std::string& table_name, const std::shared_ptr<Node> column ) const
{}

void Schema::add_index( const std::string& table_name, const std::shared_ptr<Node> index ) const
{}

void Schema::dump_schema() const
{}
