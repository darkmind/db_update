// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"
#include "Schema/Reader.hpp"

#include <string>

class XML_Handler : public Reader
{
public:
    XML_Handler();
    ~XML_Handler();

    void get_table() const override;

    void get_column() const override;

    void get_index() const override;

    mysql_rows execute( const std::string& statement ) const override;

    void dump_schema() const;

    void read_schema();

};

