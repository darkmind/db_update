// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Node.hpp"
#include <string>
#include <utility>
#include <set>
#include <map>
#include <memory>

using namespace std;

Node::Node( const string& name ) : node_name(name)
{
}

Node::~Node()
{
}

string Node::get_name() {
    return node_name;
}

void Node::set_parent( const shared_ptr<Node> parent_node ) {
    parent = weak_ptr<Node>(parent_node);
}


shared_ptr<Node> Node::get_parent() {
    return shared_ptr<Node>(parent);
}

void Node::add_child( const shared_ptr<Node> node ) {
    children.insert( make_pair( node->get_name(), node ) );
}

shared_ptr<Node> Node::get_child( const string& name ) {
    auto result = children.find(name);
    if ( result != children.end() ) {
        return result->second;
    }
    else {
        return nullptr;
    }
}

unordered_map<string, shared_ptr<Node>> Node::get_children() {
    return children;
}

void Node::add_data( const string& key, const string& value ) {
    data.insert( make_pair( key, value ) );
}

map<string, string> Node::get_data() {
    return data;
}

bool Node::has_children() {
    if ( children.size() > 0 ) {
        return true;
    }
    else {
        return false;
    }
}
