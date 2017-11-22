// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"
#include <Schema/Reader.hpp>
#include <Schema/DB/Broker.hpp>
#include <Schema/Tree/Tree.hpp>
#include <Schema/Tree/Node.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#include <cppconn/resultset.h>

class IO : public Reader
{
public:

    explicit IO( const std::unordered_map<std::string, std::string>& options );

    void read_schema( const std::string& force = "" ) override;

    std::shared_ptr<Node> get_table( const std::string& table_name = "" ) override;

    std::shared_ptr<Node> get_column( const std::string& table_name = "" ) override;

    std::shared_ptr<Node> get_index( const std::string& table_name = "" ) override;

    mysql_rows execute( const std::string& statement ) const override;

    void dump_schema() const override;

private:

    const std::string get_tables_sql = "SELECT table_name, engine, table_collation, create_options,"
        " 'table' AS type"
        " FROM information_schema.tables"
        " WHERE table_schema = DATABASE()"
        " AND ( ? IS NULL OR table_name = ? )"
        " AND table_type = 'BASE TABLE' ORDER BY table_name";

    const std::string get_cols_sql = "SELECT c.column_name, c.ordinal_position, c.column_default, c.is_nullable,"
        " c.column_type, c.extra, c.character_set_name, c.collation_name, c.table_name,"
        " 'column' AS type"
        " FROM information_schema.columns c"
        " INNER JOIN information_schema.tables t ON c.table_name = t.table_name"
        " WHERE t.table_type = 'BASE TABLE'"
        " AND c.table_schema = DATABASE()"
        " AND ( ? IS NULL OR c.table_name = ? )"
        " AND t.table_schema = DATABASE()"
        " ORDER BY c.table_name, c.ordinal_position";

    const std::string get_idx_sql = "SELECT table_name, index_name, non_unique, column_name,"
        " seq_in_index, collation, sub_part, nullable, index_type,"
        " 'index' AS type"
        " FROM information_schema.statistics"
        " WHERE table_schema = DATABASE()"
        " AND ( ? IS NULL OR table_name = ? )"
        " ORDER BY table_name, index_name, seq_in_index";

    std::unique_ptr<Broker> broker;

};

