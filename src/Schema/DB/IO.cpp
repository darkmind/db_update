// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include <Schema/DB/IO.hpp>
#include <Schema/DB/Broker.hpp>

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

using namespace std;

IO::IO( const unordered_map<string, string>& options )
{
    broker = unique_ptr<Broker>( new Broker(options) );
}

mysql_rows IO::execute ( const std::string& statement ) const
{
    const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(statement) );
    sql::ResultSetMetaData* res_meta        = result->getMetaData();
    const unsigned int c_num                = res_meta->getColumnCount();
    mysql_rows records;
    while ( result->next() ) {
        vector<string> record_row;
        for( unsigned int i = 1; i <= c_num; i++ ) {
            if(result->isNull(i)) {
                record_row.push_back("NULL");
            } else {
                record_row.push_back( result->getString(i) );
            }
        }
        records.push_back(record_row);
    }

    return records;
}

void IO::get_table() const
{}

void IO::get_column() const
{}

void IO::get_index() const
{}
