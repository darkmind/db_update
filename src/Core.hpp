// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include "Types.hpp"
#include "DB/Broker.hpp"
#include "IO/IO.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>


class Core
{
  public:
    explicit Core( const std::map<std::string, std::string>& options );

    mysql_rows execute( const std::string& statement );

    void get_schema( const std::string& table_name );

    std::shared_ptr<Schema> get_schema_ref();

  private:
    std::shared_ptr<Broker> broker;
    std::shared_ptr<IO> io;
    std::shared_ptr<Schema> schema;
};
