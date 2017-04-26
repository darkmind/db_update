// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <IO/IO.hpp>
#include <DB/Broker.hpp>
#include <DB/Node.hpp>
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

void IO::get_tables_schema( shared_ptr<Schema> schema, const unordered_map<string,string>& args )
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

    shared_ptr<Node> table_info;
    shared_ptr<Node> table_obj;

    string column_name;

    while ( result->next() ) {
        table_info = shared_ptr<Node>( new Node("table_info") );
        for( unsigned int i = 1; i <= c_num; i++ ) {
            column_name = res_meta->getColumnName(i);
            if( column_name == "TABLE_NAME" ) {
                table_obj = shared_ptr<Node>( new Node( result->getString(i) ) );
            }
            if( result->isNull(i) ) {
                table_info->add_data( column_name, "NULL" );
            } else {
                table_info->add_data( column_name, result->getString(i) );
            }
        }
        table_obj->add_child(table_info);
        table_info->set_parent(table_obj);

        schema->add_table_info(table_obj);
    }

    this->get_cols_for_tables(schema);

    return ;
}

void IO::get_cols_for_tables( shared_ptr<Schema> schema ) {
    const vector<string> tables = schema->get_tables_list();

    if ( tables.size() ) {
        shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
            broker->get_connection()->prepareStatement(get_cols_sql) );

        for ( auto it : tables ) {
            prep_stmt->setString( 1, it );
            const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );
            sql::ResultSetMetaData* res_meta        = result->getMetaData();
            const unsigned int c_num                = res_meta->getColumnCount();

            shared_ptr<Node> table   = shared_ptr<Node>( new Node( it ) );
            shared_ptr<Node> columns = shared_ptr<Node>( new Node("columns") );
            table->add_child(columns);
            columns->set_parent(table);

            shared_ptr<Node> column;
            string col;

            while ( result->next() ) {
                for( unsigned int i = 1; i <= c_num; i++ ) {
                    col = res_meta->getColumnName(i);
                    if( col == "COLUMN_NAME" ) {
                        column = shared_ptr<Node>( new Node( result->getString(i) ) );
                        columns->add_child(column);
                        column->set_parent(columns);
                    }
                    if(result->isNull(i)) {
                        column->add_data( col, "NULL" );
                    } else {
                        column->add_data( col, result->getString(i) );
                    }
                }
            }
            schema->add_table_columns(table);
        }
    }

    return ;
}
