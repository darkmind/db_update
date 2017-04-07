// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <DB/Schema.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <cstdlib> // NULL

using namespace std;

Schema* Schema::ms_instance = NULL;

Schema::Schema()
{
    schema = new schema_type;
}

Schema::~Schema()
{
}

Schema* Schema::Instance()
{
    if (ms_instance == NULL) {
        ms_instance = new Schema();
    }
    return ms_instance;
}

void Schema::Release()
{
    if (ms_instance) {
        delete ms_instance;
    }
    ms_instance = NULL;
}

void Schema::print_schema() {
    for ( auto it : *schema ) {
        cout << "[ " << it.first << " ]" << endl << endl;
        for ( auto& tbls : it.second) {
            cout << " [table name] " << tbls.first << endl;

            cout << "   [table_info]" << endl;
            auto& tbl = boost::get<basic_type>( tbls.second.at("table_info") );
            for ( auto& opt : tbl ) {
                cout << "      [" << opt.first << "] -> " << opt.second << endl;
            }

            cout << "   [columns]" << endl;
            auto& cols = boost::get<column_type>( tbls.second.at("columns") );
            for ( auto& col : cols ) {
                cout << "     [" << col.first << "]" << endl;
                for ( auto& opt : col.second ) {
                    cout << "      [" << opt.first << "] -> " << opt.second << endl;
                }
            }

            cout << endl;
        }
    }
    cout << endl;
}

void Schema::add_table_columns( string table_name, table_property columns ) {
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

void Schema::add_table_info( string table_name, table_property table_info ) {
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
        for ( auto& tbls : it.second) {
            tables.push_back(tbls.first);
        }
    }

    return tables;
}

