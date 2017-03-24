// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <DB/Broker.hpp>
#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace broker;
using namespace std;

namespace core
{

class Core
{
public:
    Core(map<string, string>);

    vector<vector<string> > execute(string);

private:
    Broker* broker;
};
}
