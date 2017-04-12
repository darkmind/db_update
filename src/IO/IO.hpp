// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <DB/Broker.hpp>
#include <DB/Schema.hpp>
#include <Types.hpp>
#include <cppconn/resultset.h>


class IO
{
public:
    explicit IO( std::shared_ptr<Broker> brokerref );

    void get_tables_schema( std::shared_ptr<Schema> schema, std::unordered_map<std::string,std::string> args );

    void get_cols_for_tables( std::shared_ptr<Schema> schema );

private:
    const std::string get_tables_sql = "SELECT TABLE_NAME, ENGINE, TABLE_COLLATION, CREATE_OPTIONS"
            "  FROM information_schema.TABLES"
            "  WHERE TABLE_SCHEMA=DATABASE()"
            "  AND ( ? IS NULL OR table_name = ? )"
            "  AND TABLE_TYPE='BASE TABLE' ORDER BY TABLE_NAME";

    const std::string get_cols_sql = "SELECT c.COLUMN_NAME, c.COLUMN_DEFAULT, c.IS_NULLABLE,"
            " c.COLUMN_TYPE, c.EXTRA, c.CHARACTER_SET_NAME, c.COLLATION_NAME"
        " FROM information_schema.COLUMNS c"
        " INNER JOIN information_schema.TABLES t ON c.TABLE_NAME=t.TABLE_NAME"
        " WHERE t.TABLE_TYPE='BASE TABLE'"
        " AND c.TABLE_SCHEMA=DATABASE()"
        " AND c.table_name = ?"
        " AND t.TABLE_SCHEMA=DATABASE()"
        " ORDER BY c.TABLE_NAME, c.COLUMN_NAME";

    std::shared_ptr<Broker> broker;

};

