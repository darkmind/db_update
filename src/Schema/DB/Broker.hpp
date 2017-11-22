// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class Broker
{
public:
    explicit Broker( const std::unordered_map<std::string, std::string>& options );

    ~Broker();

    sql::ResultSet* execute( const std::string& statement );

    sql::ResultSet* execute( sql::PreparedStatement* statement );

    sql::ResultSet* execute( std::shared_ptr<sql::PreparedStatement> statement );

    void connect( std::string host,
                 std::string db,
                 std::string user,
                 std::string password );

    std::shared_ptr<sql::Connection> get_connection();

    void clean();

  private:
    sql::Driver *driver;

    std::shared_ptr<sql::Connection> connection;
};
