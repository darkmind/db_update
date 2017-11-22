// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"
#include "Schema/Reader.hpp"
#include "Schema/Tree/Node.hpp"

#include <string>
#include <unordered_map>
#include <memory>
#include <boost/property_tree/ptree.hpp>

class File_Handler : public Reader
{
public:

    File_Handler( const std::unordered_map<std::string, std::string>& options );

    void read_schema( const std::string& force = "" ) override;

    std::shared_ptr<Node> get_table( const std::string& table_name = "" ) override;

    std::shared_ptr<Node> get_column( const std::string& table_name = "" ) override;

    std::shared_ptr<Node> get_index( const std::string& table_name = "" ) override;

    mysql_rows execute( const std::string& statement ) const override;

    void dump_schema() const override;

    ~File_Handler();

private:

    std::string file;

    void load_json_schema( const std::pair<std::string,boost::property_tree::ptree>& kv, std::shared_ptr<Node> parent_node );

    void create_json_schema( boost::property_tree::ptree& json_schema, const std::shared_ptr<Node> node, std::string parent ) const;
};

