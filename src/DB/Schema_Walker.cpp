// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Schema_Walker.hpp"
#include <Types.hpp>
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

void Schema_Walker::travel_schema( const shared_ptr<schema_type> schema ) {
    for ( auto it : *schema ) {
        cout << it.first << endl;
        Schema_Walker::travel( it.second );
    }
}

template< typename T >
void Schema_Walker::travel( T leaf ) {
    Schema_Walker::counter++;
    for ( auto it : leaf ) {
        cout << string( Schema_Walker::counter, ' ' ) << it.first << endl;
        Schema_Walker::travel( it.second );
    }
    Schema_Walker::counter--;
}
void Schema_Walker::travel( info leaf_b ) {
    if( auto* col_leaf = boost::get<column_type>(&leaf_b) ) {
        Schema_Walker::travel(*col_leaf);
    }
    else {
        auto bs_leaf = boost::get<basic_type>(leaf_b);
        Schema_Walker::travel(bs_leaf);
    }
}
void Schema_Walker::travel( basic_type leaf ) {
    Schema_Walker::counter++;
    for ( auto it : leaf ) {
        cout << string( Schema_Walker::counter, ' ' ) << it.first <<  " => " << (it.second.empty() ? "''" : it.second) << endl;
    }
    Schema_Walker::counter--;
}


