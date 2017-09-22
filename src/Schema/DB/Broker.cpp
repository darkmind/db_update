// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Schema/DB/Broker.hpp"

#include <vector>
#include <array>
#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <stdexcept>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>

using namespace std;

Broker::Broker( const unordered_map<string, string>& options )
{
    connect( options.at("host"), options.at("db"), options.at("user"), options.at("pass") );
}


sql::ResultSet* Broker::execute( const string& statement )
{
    sql::ResultSet* result;
    try {
        sql::Statement *stmt = connection->createStatement();
        result = stmt->executeQuery(statement);
        delete stmt;
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        throw runtime_error("");
    }

    return result;
}

sql::ResultSet* Broker::execute( sql::PreparedStatement* statement )
{
    sql::ResultSet* result;
    try {
        result = statement->executeQuery();
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        throw runtime_error("");
    }

    return result;
}

sql::ResultSet* Broker::execute( shared_ptr<sql::PreparedStatement> statement )
{
    sql::ResultSet* result;
    try {
        result = statement->executeQuery();
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        throw runtime_error("");
    }

    return result;
}

void Broker::connect( const string host, const string db, const string user, const string password )
{
    try {
        driver = get_driver_instance();
        ostringstream dsn;
        dsn << "tcp://" << host << ":3306";
        connection = unique_ptr<sql::Connection>( driver->connect( dsn.str(), user, password ) );
        connection->setSchema(db);
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        throw runtime_error("");
    }
}


Broker::~Broker()
{
    driver->threadEnd();
}
