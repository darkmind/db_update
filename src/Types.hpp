// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <string>
#include <vector>
#include <map>

typedef std::vector<std::vector<std::string>> mysql_rows;

typedef
    std::map <
        std::string,
        std::map <std::string,
            std::string>
    >
tbl_schema;
