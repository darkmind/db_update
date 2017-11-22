// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core.hpp"
#include "Types.hpp"
#include "Schema.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

Core::Core( const unordered_map<string, string>& in_options )
{
    schema_db   = unique_ptr<Schema<IO>>( new Schema<IO>(in_options) );
    schema_file = unique_ptr<Schema<File_Handler>>( new Schema<File_Handler>(in_options) );
    options     = in_options;
}

mysql_rows Core::execute( const string& statement )
{
    return schema_db->execute_direct_sql(statement);
}

bool Core::run_check() const
{
    return true;
}

void Core::dump_schema() const {
    schema_db->read_schema();
    schema_file->set_tree( schema_db->get_tree() );
    schema_file->dump_schema();
}

void Core::print_schema() const {
    schema_db->get_tree()->dump_tree();
}

void Core::test_method() {
    schema_file->read_schema();
    schema_file->get_tree()->dump_tree();
}
