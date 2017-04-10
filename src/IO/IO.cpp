// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <IO/IO.hpp>
#include <DB/Broker.hpp>
#include <Types.hpp>
#include <DB/Schema.hpp>

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

using namespace std;

IO::IO( std::shared_ptr<Broker> brokerref )
{
    broker = brokerref;
}

void IO::get_tables_schema( shared_ptr<Schema> schema, const unordered_map<string,string> args )
{
    shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
        broker->get_connection()->prepareStatement(get_tables_sql) );

    auto param = args.find("table_name");
    if ( param != args.end() && ! param->second.empty() ) {
        prep_stmt->setString( 1, param->second );
        prep_stmt->setString( 2, param->second );
    }
    else {
        prep_stmt->setNull( 1, sql::DataType::SQLNULL );
        prep_stmt->setNull( 2, sql::DataType::SQLNULL );
    }

    const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );

    sql::ResultSetMetaData* res_meta = result->getMetaData();
    const unsigned int c_num = res_meta->getColumnCount();

    basic_type options;
    string table_name;
    string column_name;

    while ( result->next() ) {
        for( unsigned int i = 1; i <= c_num; i++ ) {
            column_name = res_meta->getColumnName(i);
            if( column_name == "TABLE_NAME" ) {
                table_name = result->getString(i);
            }
            if( result->isNull(i) ) {
                options[column_name] = "NULL";
            } else {
                options[column_name] = result->getString(i);
            }
        }
        table_property table_info = {{ "table_info", options }};
        schema->add_table_info( table_name, table_info );
    }

    this->get_cols_for_tables(schema);

    return ;
}

void IO::get_cols_for_tables( shared_ptr<Schema> schema ) {
    const vector<string> tables = schema->get_tables_list();

    if ( tables.size() ) {
        shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
            broker->get_connection()->prepareStatement(get_cols_sql) );

        auto it = tables.begin();
        while ( it != tables.end() ) {
            prep_stmt->setString( 1, *it );
            const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );
            sql::ResultSetMetaData* res_meta        = result->getMetaData();
            const unsigned int c_num                = res_meta->getColumnCount();

            string column_name;
            string col;
            basic_type options;
            column_type column;
            table_property columns;

            while ( result->next() ) {
                for( unsigned int i = 1; i <= c_num; i++ ) {
                    col = res_meta->getColumnName(i);
                    if( col == "COLUMN_NAME" ) {
                        column_name = result->getString(i);
                    }
                    if(result->isNull(i)) {
                        options[col] = "NULL";
                    } else {
                        options[col] = result->getString(i);
                    }
                }
                column.insert( {{ column_name, options }} );
            }
            columns.insert( {{ "columns", column }} );
            schema->add_table_columns( *it, columns );

            it++;
        }
    }

    return ;
}
