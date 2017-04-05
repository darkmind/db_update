// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <IO/IO.hpp>
#include <DB/Broker.hpp>
#include <Types.hpp>

#include <string>
#include <vector>
#include <unordered_map>

#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

using namespace std;

IO::IO(Broker * brokerref)
{
    broker = brokerref;
}

schema_type IO::get_tables_schema( schema_type& schema, unordered_map<string,string> args )
{
    sql::PreparedStatement* prep_stmt = broker->get_connection()->prepareStatement(get_tables_sql);
    auto param = args.find("table_name");
    if ( param != args.end() && ! param->second.empty() ) {
        prep_stmt->setString( 1, param->second );
        prep_stmt->setString( 2, param->second );
    }
    else {
        prep_stmt->setNull( 1, sql::DataType::SQLNULL );
        prep_stmt->setNull( 2, sql::DataType::SQLNULL );
    }

    sql::ResultSet* result = broker->execute(prep_stmt);

    sql::ResultSetMetaData *res_meta = result->getMetaData();
    unsigned int c_num = res_meta->getColumnCount();
    table_type table;
    vector<table_type> tables;
    string table_name;
    string column_name;
    while (result->next()) {
        for(unsigned int i = 1; i <= c_num; i++) {
            column_name = res_meta->getColumnName(i);
            if( column_name == "table_name" ) {
                table_name = result->getString(i);
                continue;
            }
            if(result->isNull(i)) {
                table[table_name][column_name] = "NULL";
            } else {
                table[table_name][column_name] = result->getString(i);
            }
        }
        tables.push_back(table);
    }
    schema.insert({"table", tables});
    delete result;
    delete prep_stmt;

    return schema;
}
