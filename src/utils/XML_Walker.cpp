// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "XML_Walker.hpp"
#include <Types.hpp>
#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>

using namespace std;
namespace pt = boost::property_tree;

XML_Walker::XML_Walker()
{
}

XML_Walker::~XML_Walker()
{
}

void XML_Walker::travel( const info& leaf_b, pt::ptree& xml_schema, const string& parent ) {
    auto* col_leaf = boost::get<column_type>(&leaf_b);
    if (col_leaf) {
        XML_Walker::travel( *col_leaf, xml_schema, parent );
    }
    else {
        auto bs_leaf = boost::get<basic_type>(leaf_b);
        XML_Walker::travel( bs_leaf, xml_schema, parent );
    }
}
void XML_Walker::travel( const basic_type& leaf, pt::ptree& xml_schema, const string& parent ) {
    for ( auto it : leaf ) {
        string add_parent = parent + "." + it.first;
        xml_schema.add( add_parent, it.second );
    }
}
template< typename T, typename SCHEMA, typename PARENT >
void XML_Walker::travel( const T& leaf, SCHEMA& xml_schema, const PARENT& parent ) {
    for ( auto it : leaf ) {
        string add_parent;
        if ( parent.empty() ) {
            add_parent = it.first;
        }
        else {
            add_parent = parent + "." + it.first;
        }

        XML_Walker::travel( it.second, xml_schema, add_parent );
    }
}


void XML_Walker::populate_schema( const shared_ptr<schema_type> schema, pt::ptree& xml_schema ) {
    travel( *schema, xml_schema, (string)"" );
}

