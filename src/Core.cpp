// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Core.hpp>
#include <Types.hpp>
#include <DB/Broker.hpp>
#include <DB/Schema.hpp>
#include <IO/IO.hpp>
#include <memory>
#include <map>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <vector>

using namespace std;

Core::Core(map<string, string> options)
{
    broker = shared_ptr<Broker>( new Broker() );
    broker->connect(options.at("host"), options.at("db"), options.at("user"), options.at("pass"));
    io     = shared_ptr<IO>( new IO(broker) );
    schema = shared_ptr<Schema>( new Schema() );
}

mysql_rows Core::execute(string statement)
{
    unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(statement) );
    sql::ResultSetMetaData* res_meta = result->getMetaData();
    unsigned int c_num = res_meta->getColumnCount();
    mysql_rows records;
    while (result->next()) {
        vector<string> record_row;
        for(unsigned int i = 1; i <= c_num; i++) {
            if(result->isNull(i)) {
                record_row.push_back("NULL");
            } else {
                record_row.push_back(result->getString(i));
            }
        }
        records.push_back(record_row);
    }

    return records;
}

void Core::get_schema(const string table_name)
{
    unordered_map<string, string> args = {{ "table_name", table_name }};
    io->get_tables_schema(schema, args);
}

shared_ptr<Schema> Core::get_schema_ref() {
    return schema;
}
