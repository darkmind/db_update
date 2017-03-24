// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>
#include <array>
#include <string>

namespace broker
{

class Broker
{
  public:
    ~Broker();
    
    std::vector<std::vector<std::string> > prepare_and_execute( std::string sql, std::vector<std::string> args );
    
    sql::ResultSet* execute(std::string statement);

    void connect(std::string host,
                 std::string db,
                 std::string user,
                 std::string password);
            
    void clean();

  private:
    sql::Driver *driver;
    sql::Connection *connection;
    sql::Statement *stmt;
    sql::ResultSet *res;
};
}
