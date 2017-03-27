// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <IO/IO.hpp>
#include <DB/Broker.hpp>
#include <vector>
#include <string>
#include <cppconn/resultset.h>

using namespace std;

IO::IO(Broker * brokerref)
{
    broker = brokerref;
}

sql::ResultSet* IO::get_tables_schema( const vector<string> args )
{
    return broker->prepare_and_execute( get_tables_sql, args );
}