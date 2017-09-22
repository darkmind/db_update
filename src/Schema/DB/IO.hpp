// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"
#include <Schema/Reader.hpp>
#include <Schema/DB/Broker.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#include <cppconn/resultset.h>

class IO : public Reader
{
public:
    explicit IO( const std::unordered_map<std::string, std::string>& options );

    void get_table() const override;

    void get_column() const override;

    void get_index() const override;

    mysql_rows execute( const std::string& statement ) const override;

private:
    const std::string get_tables_sql = "SELECT table_name, engine, table_collation, create_options"
            " FROM information_schema.tables"
            " WHERE table_schema = DATABASE()"
            " AND ( ? IS NULL OR table_name = ? )"
            " AND table_type = 'BASE TABLE' ORDER BY table_name";

    const std::string get_cols_sql = "SELECT c.column_name, c.ordinal_position, c.column_default, c.is_nullable,"
            " c.column_type, c.extra, c.character_set_name, c.collation_name, c.table_name"
        " FROM information_schema.columns c"
        " INNER JOIN information_schema.tables t ON c.table_name = t.table_name"
        " WHERE t.table_type = 'BASE TABLE'"
        " AND c.table_schema = DATABASE()"
        " AND c.table_name = ?"
        " AND t.table_schema = DATABASE()"
        " ORDER BY c.table_name, c.column_name, c.ordinal_position";

    std::unique_ptr<Broker> broker;

};

