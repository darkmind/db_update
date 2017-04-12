// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <memory>
#include <string>
#include <DB/Schema.hpp>

class Check
{
public:
    static bool run( const std::shared_ptr<Schema> schema, const std::string& ref_schema_file );
};

