// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core.hpp"
#include "Types.hpp"
#include "Schema.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

Core::Core( const unordered_map<string, string>& in_options ) :
    schema_db( unique_ptr<Schema>( new Schema( in_options, 1 ) ) ), // 1 - db
    schema_file( unique_ptr<Schema>( new Schema( in_options, 2 ) ) ), // 2 - file
    options(in_options)
{
}

mysql_rows Core::execute( const string& statement )
{
    return schema_db->execute_direct_sql(statement);
}

bool Core::run_check() const
{
    return true;
}

void Core::print_schema() const {}

