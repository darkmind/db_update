// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include <Schema/DB/IO.hpp>
#include <Schema/DB/Broker.hpp>
#include <Schema/Tree/Tree.hpp>
#include <Schema/Tree/Node.hpp>

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <iostream>

#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>

using namespace std;

IO::IO( const unordered_map<string, string>& options )
{
    broker = unique_ptr<Broker>( new Broker(options) );
    tree   = unique_ptr<Tree>( new Tree() );
}

mysql_rows IO::execute ( const string& statement ) const
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

void IO::read_schema( const string& force )
{
    if ( tree->get_root()->get_children().size() == 0 or !force.empty() ) {
        get_table();
        get_column();
        get_index();
    }
}

shared_ptr<Node> IO::get_table( const string& table_name )
{
    if ( !table_name.empty() ) {
        vector<shared_ptr<Node>> nodes = tree->find_node(table_name);
        for ( const auto node : nodes ) {
            if ( node->get_type() == "table" ) {
                return node;
            }
        }
    }

    shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
        broker->get_connection()->prepareStatement(get_tables_sql) );

    if ( !table_name.empty() ) {
        prep_stmt->setString( 1, table_name );
        prep_stmt->setString( 2, table_name );
    }
    else {
        prep_stmt->setNull( 1, sql::DataType::SQLNULL );
        prep_stmt->setNull( 2, sql::DataType::SQLNULL );
    }

    const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );
    sql::ResultSetMetaData* res_meta        = result->getMetaData();
    const unsigned int c_num                = res_meta->getColumnCount();

    while ( result->next() ) {
        shared_ptr<Node> table;
        unordered_map<string, string> node_data;
        for( unsigned int i = 1; i <= c_num; i++ ) {
            node_data.insert( make_pair( res_meta->getColumnLabel(i), result->getString(i) ) );

            if ( res_meta->getColumnLabel(i) == "table_name" ) {
                table = shared_ptr<Node>( new Node( result->getString(i) ) );
                tree->get_root()->add_child(table);
                table->set_parent( tree->get_root() );
            }
        }
        table->set_data(node_data);
        table->set_type("table");
    }

    return nullptr;
}

shared_ptr<Node> IO::get_column( const string& table_name )
{
    if ( !table_name.empty() ) {
        vector<shared_ptr<Node>> nodes = tree->find_node(table_name);
        for ( const auto node : nodes ) {
            if ( node->get_type() == "column" ) {
                return node;
            }
        }
    }

    shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
        broker->get_connection()->prepareStatement(get_cols_sql) );

    if ( !table_name.empty() ) {
        prep_stmt->setString( 1, table_name );
        prep_stmt->setString( 2, table_name );
    }
    else {
        prep_stmt->setNull( 1, sql::DataType::SQLNULL );
        prep_stmt->setNull( 2, sql::DataType::SQLNULL );
    }

    const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );
    sql::ResultSetMetaData* res_meta        = result->getMetaData();
    const unsigned int c_num                = res_meta->getColumnCount();

    while ( result->next() ) {
        shared_ptr<Node> table;
        unordered_map<string, string> node_data {};
        string column_name;

        for( unsigned int i = 1; i <= c_num; i++ ) {
            node_data.insert( make_pair( res_meta->getColumnLabel(i), result->getString(i) ) );

            if ( res_meta->getColumnLabel(i) == "table_name" ) {
                vector<shared_ptr<Node>> nodes = tree->find_node( result->getString(i) );
                for ( const auto node : nodes ) {
                    if ( node->get_type() == "table" ) {
                        table = node;
                    }
                }

                if (! table) {
                    table = shared_ptr<Node>( new Node( result->getString(i) ) );
                    tree->get_root()->add_child(table);
                    table->set_parent( tree->get_root() );
                }
            }
            else if ( res_meta->getColumnLabel(i) == "column_name" ) {
                column_name = result->getString(i);
            }
        }

        shared_ptr<Node> column = shared_ptr<Node>( new Node(column_name) );
        table->add_child(column);
        column->set_parent(table);
        column->set_type("column");

        column->set_data(node_data);
    }

    return nullptr;
}

shared_ptr<Node> IO::get_index( const string& table_name )
{
    if ( !table_name.empty() ) {
        vector<shared_ptr<Node>> nodes = tree->find_node(table_name);
        for ( const auto node : nodes ) {
            if ( node->get_type() == "index" ) {
                return node;
            }
        }
    }

    shared_ptr<sql::PreparedStatement> prep_stmt = shared_ptr<sql::PreparedStatement>(
        broker->get_connection()->prepareStatement(get_idx_sql) );

    if ( !table_name.empty() ) {
        prep_stmt->setString( 1, table_name );
        prep_stmt->setString( 2, table_name );
    }
    else {
        prep_stmt->setNull( 1, sql::DataType::SQLNULL );
        prep_stmt->setNull( 2, sql::DataType::SQLNULL );
    }

    const unique_ptr<sql::ResultSet> result = unique_ptr<sql::ResultSet>( broker->execute(prep_stmt) );
    sql::ResultSetMetaData* res_meta        = result->getMetaData();
    const unsigned int c_num                = res_meta->getColumnCount();

    while ( result->next() ) {
        shared_ptr<Node> table;
        unordered_map<string, string> node_data {};
        string index_name = "";

        for( unsigned int i = 1; i <= c_num; i++ ) {
            node_data.insert( make_pair( res_meta->getColumnLabel(i), result->getString(i) ) );

            if ( res_meta->getColumnLabel(i) == "table_name" ) {
                vector<shared_ptr<Node>> nodes = tree->find_node( result->getString(i) );
                for ( const auto node : nodes ) {
                    if ( node->get_type() == "table" ) {
                        table = node;
                    }
                }

                if (! table) {
                    table = shared_ptr<Node>( new Node( result->getString(i) ) );
                    tree->get_root()->add_child(table);
                    table->set_parent( tree->get_root() );
                }
            }
            else if ( res_meta->getColumnLabel(i) == "index_name" ) {
                index_name = result->getString(i);
            }
        }

        shared_ptr<Node> index;
        shared_ptr<Node> attributes;

        vector<shared_ptr<Node>> nodes = tree->find_node( index_name, table );

        for ( const auto& node : nodes ) {
            if ( node->get_type() == "index" ) {
                index      = node;
                attributes = index->get_child("attributes");
            }
        }

        if (! index) {
            index = shared_ptr<Node>( new Node(index_name) );
            table->add_child(index);
            index->set_parent(table);
            index->set_type("index");
            attributes = shared_ptr<Node>( new Node("attributes") );
            index->add_child(attributes);
            attributes->set_parent(index);
        }

        shared_ptr<Node> index_entry = shared_ptr<Node>( new Node( node_data.at("column_name") ) );
        index_entry->set_data(node_data);

        attributes->add_child(index_entry);
        index_entry->set_parent(attributes);
    }

    return nullptr;
}

void IO::dump_schema() const
{}
