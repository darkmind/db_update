// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Schema.hpp"
#include "Schema_Walker.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

Schema::Schema() : schema( shared_ptr<schema_type>( new schema_type ) )
{}

void Schema::print_schema() {
    Schema_Walker::travel_schema(schema);
}

void Schema::add_table_columns( const string& table_name, const table_property& columns ) {
    unordered_map<string, table_property> tbl = {{ table_name, columns }};

    auto tables = schema->find("tables");
    if ( tables == schema->end() ) {
        schema->insert( {{ "tables", tbl }} );
    }
    else {
        auto table = tables->second.find(table_name);
        if ( table != tables->second.end() ) {
            info desc = columns.at("columns");
            table->second.insert( {{ "columns", desc }} );
        }
        else {
            tables->second.insert( {table_name, columns} );
        }
    }

    return ;
}

void Schema::add_table_info( const string& table_name, const table_property& table_info ) {
    auto tables = schema->find("tables");
    if ( tables == schema->end() ) {
        unordered_map<string, table_property> tbl = {{ table_name, table_info }};
        schema->insert( {{ "tables", tbl }} );
    }
    else {
        tables->second.insert( {table_name, table_info} );
    }

    return ;
}

vector<string> Schema::get_tables_list() {
    vector<string> tables;

    for ( auto it : *schema ) {
        for ( auto& tbls : it.second ) {
            tables.push_back(tbls.first);
        }
    }

    return tables;
}

shared_ptr<schema_type> Schema::get_schema()
{
    return schema;
}

