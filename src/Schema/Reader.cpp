// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Reader.hpp"

using namespace std;

Reader::Reader()
{}

shared_ptr<Tree> Reader::get_tree() const
{
    return tree;
}

void Reader::set_tree( std::shared_ptr<Tree> in_tree )
{
    tree = in_tree;
}

Reader::~Reader()
{}
