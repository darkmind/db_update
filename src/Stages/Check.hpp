// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <memory>
#include <string>
#include "DB/Node.hpp"
#include "DB/Schema.hpp"
#include <boost/property_tree/ptree.hpp>

class Check
{
public:
    static bool run( const std::shared_ptr<Schema> schema, const std::string& ref_schema_file );
private:
    static void check_schema(
        const std::shared_ptr<Node> db_schema,
        const boost::property_tree::ptree& ref_schema,
        const std::string& parent,
        bool& flag );

    static std::size_t counter;
};

