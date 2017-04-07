// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>

typedef std::vector<std::vector<std::string>> mysql_rows;

typedef
    std::unordered_map <
        std::string,
        std::string
    >
basic_type;

typedef
    std::unordered_map <
        std::string,          // column name
        basic_type
    >
column_type;

typedef
    boost::variant< column_type, basic_type >
info;

typedef
    std::unordered_map <
        std::string,         // "columns", "table_info"
        info
    >
table_property;

typedef
    std::unordered_map <
      std::string,           // "tables", "indexes", etc
      std::unordered_map <
        std::string,         // table name as a key to table_type
        table_property
      >
    >
schema_type;


// schema:
//   "tables":
//     <table_name>:
//       "table_info":
//         <option> = <value>
//         ...
//     ...
//       "columns":
//         <column_name>:
//           <option> = <value>
//           ...
//         ...
