// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include "Schema.hpp"
#include "Schema/DB/IO.hpp"
#include "Schema/File/File_Handler.hpp"
#include "Schema/Tree/Tree.hpp"
#include "Schema/Tree/Node.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>

using namespace std;

template <class READER_T>
Schema<READER_T>::Schema( const unordered_map<string, string>& options )
{
    io = unique_ptr<READER_T>( new READER_T(options) );
}

template <class READER_T>
mysql_rows Schema<READER_T>::execute_direct_sql ( const std::string& statement ) const
{
    return io->execute(statement);
}

template <class READER_T>
void Schema<READER_T>::get_table() const
{}

template <class READER_T>
void Schema<READER_T>::get_table( const std::string& table_name ) const
{}

template <class READER_T>
void Schema<READER_T>::get_column( const std::string& table_name ) const
{}
template <class READER_T>
void Schema<READER_T>::get_column( const std::string& table_name, const std::string& column_name ) const
{}

template <class READER_T>
void Schema<READER_T>::get_index( const std::string& table_name ) const
{}
template <class READER_T>
void Schema<READER_T>::get_index( const std::string& table_name, const std::string& index_name ) const
{}

template <class READER_T>
void Schema<READER_T>::add_table( const std::shared_ptr<Node> table ) const
{}

template <class READER_T>
void Schema<READER_T>::add_column( const std::string& table_name, const std::shared_ptr<Node> column ) const
{}

template <class READER_T>
void Schema<READER_T>::add_index( const std::string& table_name, const std::shared_ptr<Node> index ) const
{}

template <class READER_T>
void Schema<READER_T>::dump_schema() const
{
    io->dump_schema();
}

template <class READER_T>
void Schema<READER_T>::read_schema()
{
    io->read_schema();
}

template <class READER_T>
std::shared_ptr<Tree> Schema<READER_T>::get_tree() const
{
    return io->get_tree();
}

template <class READER_T>
void Schema<READER_T>::set_tree( shared_ptr<Tree> tree )
{
    io->set_tree(tree);
}

template class Schema<IO>;
template class Schema<File_Handler>;
