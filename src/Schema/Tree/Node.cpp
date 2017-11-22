// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Node.hpp"

#include <string>
#include <utility>
#include <set>
#include <unordered_map>
#include <memory>
#include <vector>
#include <regex>
#include <iostream>

using namespace std;

Node::Node( const string& name ) : node_name(name)
{
    if ( name == "" ) {
        throw runtime_error("Node can't have empty name.");
    }
}

Node::~Node() {}

string Node::get_name() const {
    return node_name;
}

void Node::set_parent( const shared_ptr<Node> parent_node ) {
    parent = weak_ptr<Node>(parent_node);
}


shared_ptr<Node> Node::get_parent() const {
    return shared_ptr<Node>(parent);
}

void Node::add_child( const shared_ptr<Node> node ) {
    children.push_back(node);
}

shared_ptr<Node> Node::get_child( const string& name ) const {
    regex re( "^" + name + "$" );
    for ( const auto it : children ) {
        if ( regex_match( it->get_name(), re ) ) {
            return it;
        }
    }
    return nullptr;
}

vector<shared_ptr<Node>> Node::get_children() const {
    return children;
}

void Node::add_data( const string& key, const string& value ) {
    data.insert( make_pair( key, value ) );
}

void Node::set_data( const unordered_map<string, string>& in_data ) {
    data = in_data;
}

unordered_map<string, string> Node::get_data() const {
    return data;
}

void Node::set_type( const string& i_type ) {
    type = i_type;
}

string Node::get_type() const {
    return type;
}

bool Node::has_children() const {
    if ( children.size() > 0 ) {
        return true;
    }
    else {
        return false;
    }
}
