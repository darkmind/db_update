// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"

#include <string>
#include <memory>

#include "Schema/Tree/Tree.hpp"

class Reader
{
public:

    Reader();
    ~Reader();

    virtual void read_schema( const std::string& force = "" ) = 0;

    virtual std::shared_ptr<Node> get_table( const std::string& table_name = "" ) = 0;

    virtual std::shared_ptr<Node> get_column( const std::string& table_name = "" ) = 0;

    virtual std::shared_ptr<Node> get_index( const std::string& table_name = "" ) = 0;

    virtual mysql_rows execute( const std::string& statement ) const = 0;

    virtual void dump_schema() const = 0;

    std::shared_ptr<Tree> get_tree() const;

    void set_tree( std::shared_ptr<Tree> in_tree );

protected:

    std::shared_ptr<Tree> tree;
};

