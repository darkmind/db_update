// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>

#include <Types.hpp>

class XML_Walker
{
public:
    XML_Walker();
    ~XML_Walker();

    static void populate_schema( const std::shared_ptr<schema_type> schema, boost::property_tree::ptree& xml_schema );

    template< typename T, typename SCHEMA, typename PARENT >
    static void travel( const T& leaf, SCHEMA& xml_schema, const PARENT& parent  );
    static void travel( const info& leaf_b, boost::property_tree::ptree& xml_schema, const std::string& parent );
    static void travel( const basic_type& leaf, boost::property_tree::ptree& xml_schema, const std::string& parent  );

};
