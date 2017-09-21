// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"

#include <string>

class Reader
{
public:

    virtual void get_table() const = 0;

    virtual void get_column() const = 0;

    virtual void get_index() const = 0;

    virtual mysql_rows execute( const std::string& statement ) const = 0;
};

