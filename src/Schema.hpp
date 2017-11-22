// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include "Types.hpp"
#include "Schema/Reader.hpp"
#include "Schema/Tree/Tree.hpp"
#include "Schema/Tree/Node.hpp"
#include "Schema/DB/IO.hpp"
#include "Schema/DB/Broker.hpp"
#include "Schema/File/File_Handler.hpp"

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

template <class READER_T>
class Schema
{

public:

    Schema( const std::unordered_map<std::string, std::string>& options );

    mysql_rows execute_direct_sql( const std::string& statement ) const;

    void get_table() const;
    void get_table( const std::string& table_name ) const;

    void get_column( const std::string& table_name ) const;
    void get_column( const std::string& table_name, const std::string& column_name ) const;

    void get_index( const std::string& table_name ) const;
    void get_index( const std::string& table_name, const std::string& index_name ) const;

    void add_table( const std::shared_ptr<Node> table ) const;
    void add_column( const std::string& table_name, const std::shared_ptr<Node> column ) const;
    void add_index( const std::string& table_name, const std::shared_ptr<Node> index ) const;

    std::shared_ptr<Tree> get_tree() const;
    void set_tree( std::shared_ptr<Tree> tree );

    void read_schema();

    void dump_schema() const;

private:

    std::shared_ptr<READER_T> io;
};

