// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <Types.hpp>
#include <DB/Broker.hpp>
#include <IO/IO.hpp>
#include <map>
#include <string>
#include <vector>


class Core
{
  public:
    Core(std::map<std::string, std::string> options);

    ~Core();

    mysql_rows execute(std::string statement);

    mysql_rows get_schema(std::string statement);

  private:
    Broker* broker;
    IO * io;
};
