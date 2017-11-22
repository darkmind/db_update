// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Tree.hpp"
#include "Node.hpp"

#include <memory>
#include <string>
#include <regex>
#include <iostream>
#include <sstream>

using namespace std;

Tree::Tree() :
    root( shared_ptr<Node>( new Node("tables") ) )
{}

shared_ptr<Node> Tree::get_root() const
{
    return root;
}

vector<shared_ptr<Node>> Tree::find_node( const string& node_name ) const
{
    return find_node( node_name, get_root() );
}

vector<shared_ptr<Node>> Tree::find_node( const string& node_name, const shared_ptr<Node> root_node ) const
{
    vector<shared_ptr<Node>> nodes;
    regex re( "^" + node_name + "$" );
    for ( const auto it : root_node->get_children() ) {
        if ( regex_match( it->get_name(), re ) ) {
            nodes.push_back(it);
        }
        for ( const auto node : find_node( node_name, it ) ) {
            nodes.push_back(node);
        }
    }

    return nodes;
}

void Tree::dump_tree( const size_t& counter, const std::shared_ptr<Node> node ) const
{
    cout << string( counter, ' ' ) << node->get_name() << endl;
    for ( auto data : node->get_data() ) {
        cout << string( counter + 1, ' ' ) <<
            data.first <<  " => " << (data.second.empty() ? "''" : data.second) <<
            endl;
    }
    cout << endl;

    if ( node->has_children() ) {
        for ( auto child : node->get_children() ) {
            Tree::dump_tree( counter + 1 , child);
        }
    }
}

void Tree::dump_tree() const
{
    Tree::dump_tree( 0, root );
}
