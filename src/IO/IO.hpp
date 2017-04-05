// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <DB/Broker.hpp>
#include <Types.hpp>
#include <cppconn/resultset.h>


class IO
{
public:
    IO(Broker* brokerref);

    schema_type get_tables_schema( schema_type& schema, std::unordered_map<std::string,std::string> args );

private:
    const std::string get_tables_sql = "SELECT TABLE_NAME, ENGINE, TABLE_COLLATION, CREATE_OPTIONS"
            "  FROM information_schema.TABLES"
            "  WHERE TABLE_SCHEMA=DATABASE()"
            "  AND ( ? IS NULL OR table_name = ? )"
            "  AND TABLE_TYPE='BASE TABLE' ORDER BY TABLE_NAME";

    Broker * broker;

};

