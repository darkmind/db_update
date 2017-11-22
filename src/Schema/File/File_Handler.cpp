// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include "File_Handler.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>

using namespace std;
namespace pt = boost::property_tree;

File_Handler::File_Handler( const unordered_map<string, string>& options )
{
    file = options.at("source_file");
    tree = unique_ptr<Tree>( new Tree() );
}

shared_ptr<Node> File_Handler::get_table( const string& table_name )
{}

shared_ptr<Node> File_Handler::get_column( const string& table_name )
{}

shared_ptr<Node> File_Handler::get_index( const string& table_name )
{}

void File_Handler::read_schema( const string& force )
{
    pt::ptree json_schema;
    try {
        pt::read_json( file, json_schema );
    }
    catch ( const exception& ex ) {
        cout << "# ERR: Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << ex.what();
        throw runtime_error("Can't parse json file");
    }

    tree = unique_ptr<Tree>( new Tree() );
    pt::ptree children = json_schema.get_child("tables");
    for ( const auto& kv : children ) {
        load_json_schema( kv, tree->get_root() );
    }

}

void File_Handler::load_json_schema ( const pair<string, pt::ptree>& kv, shared_ptr<Node> parent_node )
{
    if ( kv.first == "columns" or kv.first == "indexes" ) {
        for ( const auto& kv_s : kv.second ) {
            load_json_schema( kv_s, parent_node );
        }
    }
    else {
        shared_ptr<Node> node = shared_ptr<Node>( new Node(kv.first) );
        parent_node->add_child(node);
        node->set_parent(parent_node);

        unordered_map<string, string> attributes;
        for ( const auto& kv_s : kv.second ) {
            if ( kv_s.first != "columns" and kv_s.first != "indexes" ) {
                attributes.insert( make_pair( kv_s.first, kv_s.second.data() ) );
            }
            else {
                load_json_schema( kv_s, node );
            }
        }
        cout << "Node: " << node->get_name() << endl;
        for ( const auto& xz : attributes ) {
            cout << "Key: " << xz.first << " Val: " << xz.second <<  endl;
        }
        node->set_data(attributes);
    }
}

void File_Handler::dump_schema() const
{
    pt::ptree json_schema;
    string parent = "";
    create_json_schema( json_schema, tree->get_root(), parent );

    try {
        pt::write_json(
            file,
            json_schema
        );
    }
    catch ( const exception& ex ) {
        cout << "# ERR: Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << ex.what();
        throw runtime_error("");
    }
}

void File_Handler::create_json_schema( pt::ptree& json_schema, const shared_ptr<Node> node, string parent ) const
{
    if ( node->get_name() == "tables" ) {
        parent = "tables";
    }
    else {
        if ( node->get_type() == "column" ) {
            parent = parent + "." + "columns" + "." + node->get_name();
        }
        else if ( node->get_type() == "index" and node->get_parent()->get_type() != "index" ) {
            parent = parent + "." + "indexes" + "." + node->get_name();
        }
        else {
            parent = parent + "." + node->get_name();
        }

        for ( auto property : node->get_data() ) {
            json_schema.put( parent + "." + property.first, property.second );
        }
    }

    for ( auto it : node->get_children() ) {
        create_json_schema( json_schema, it, parent );
    }
}

mysql_rows File_Handler::execute( const string& statement ) const {
    throw runtime_error("Can't call execute on non-db Schema");
}

File_Handler::~File_Handler()
{}

