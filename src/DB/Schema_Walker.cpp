// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Schema_Walker.hpp"
#include "Node.hpp"
#include <memory>
#include <string>
#include <iostream>

using namespace std;

size_t Schema_Walker::counter = 0;

Schema_Walker::Schema_Walker()
{
}

Schema_Walker::~Schema_Walker()
{
}

void Schema_Walker::travel_schema( const shared_ptr<Node> schema ) {
    Schema_Walker::counter++;

    cout << string( Schema_Walker::counter, ' ' ) << schema->get_name() << endl;

    if ( schema->has_children() ) {
        for ( auto child : schema->get_children() ) {
            Schema_Walker::travel_schema(child.second);
        }
    }
    else {
        Schema_Walker::counter++;
        for ( auto data : schema->get_data() ) {
            cout << string( Schema_Walker::counter, ' ' ) <<
                data.first <<  " => " << (data.second.empty() ? "''" : data.second) <<
                endl;
        }
        Schema_Walker::counter--;
    }

    Schema_Walker::counter--;
}
