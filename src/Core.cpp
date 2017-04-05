// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Core.hpp>
#include <Types.hpp>
#include <DB/Broker.hpp>
#include <IO/IO.hpp>
#include <map>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <vector>

using namespace std;

Core::Core(map<string, string> options)
{
    broker = new Broker();
    broker->connect(options.at("host"), options.at("db"), options.at("user"), options.at("pass"));
    io = new IO( broker );
}

mysql_rows Core::execute(string statement)
{
    sql::ResultSet* result = broker->execute(statement);
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
    delete result;

    return records;
}

void Core::get_schema(const string table_name)
{
    unordered_map<string, string> args;
    args.insert( unordered_map<string, string>::value_type("table_name", table_name) );
    schema = io->get_tables_schema(schema, args);
}

schema_type* Core::get_schema_ref() {
    return &schema;
}

Core::~Core()
{
    delete io;
    delete broker;
}
