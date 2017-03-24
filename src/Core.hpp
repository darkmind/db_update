// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <DB/Broker.hpp>
#include <map>
#include <string>
#include <vector>

namespace core
{

class Core
{
  public:
    Core(std::map<std::string, std::string> options);

    std::vector<std::vector<std::string>> execute(std::string statement);

  private:
    broker::Broker* broker;
};
}
