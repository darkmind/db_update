// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Schema.hpp"
#include "Node.hpp"
#include "Schema_Walker.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

Schema::Schema() : schema( shared_ptr<Node>( new Node("schema") ) )
{}

void Schema::print_schema() {
    Schema_Walker::travel_schema(schema);
}

void Schema::add_table_columns( const shared_ptr<Node> table ) {
    shared_ptr<Node> tables = schema->get_child("tables");
    if (! tables) {
        tables = shared_ptr<Node>( new Node("tables") );
        schema->add_child(tables);
        tables->set_parent(schema);
    }

    shared_ptr<Node> table_obj = tables->get_child( table->get_name() );
    if (table_obj) {
        shared_ptr<Node> table_info = table->get_child("columns");
        table_obj->add_child(table_info);
        table_info->set_parent(table_obj);

    }
    else {
        tables->add_child(table);
    }

    return ;
}

void Schema::add_table_info( const shared_ptr<Node> table ) {
    shared_ptr<Node> tables = schema->get_child("tables");
    if (! tables) {
        tables = shared_ptr<Node>( new Node("tables") );
        schema->add_child(tables);
        tables->set_parent(schema);
    }

    shared_ptr<Node> table_obj = tables->get_child( table->get_name() );
    if (table_obj) {
        shared_ptr<Node> table_info = table->get_child("table_info");
        table_obj->add_child(table_info);
        table_info->set_parent(table_obj);

    }
    else {
        tables->add_child(table);
    }

    return ;
}

vector<string> Schema::get_tables_list() {
    vector<string> table_list;

    shared_ptr<Node> tables = schema->get_child("tables");
    if (! tables) {
        tables = shared_ptr<Node>( new Node("tables") );
        schema->add_child(tables);
        tables->set_parent(schema);
    }

    for ( auto it : tables->get_children() ) {
        table_list.push_back( it.first );
    }

    return table_list;
}

shared_ptr<Node> Schema::get_schema()
{
    return schema;
}

