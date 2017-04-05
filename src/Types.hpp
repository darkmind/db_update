// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

typedef std::vector<std::vector<std::string>> mysql_rows;

typedef
    std::unordered_map <
        std::string,
        std::unordered_map <
            std::string,
            std::string
        >
    >
table_type;

typedef
    std::unordered_map <
      std::string,
      std::vector<table_type>
    >
schema_type;