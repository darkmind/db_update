// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include "Types.hpp"
#include "Schema.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>


class Core
{
public:

    explicit Core( const std::unordered_map<std::string, std::string>& in_options );

    mysql_rows execute( const std::string& statement );

    bool run_check() const;

    void dump_schema() const;

    void print_schema() const;

    void test_method();

private:

    std::unique_ptr<Schema<IO>> schema_db;

    std::unique_ptr<Schema<File_Handler>> schema_file;

    std::unordered_map<std::string, std::string> options;
};
