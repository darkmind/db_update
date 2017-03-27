// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <DB/Broker.hpp>
#include <vector>
#include <array>
#include <string>
#include <sstream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/datatype.h>

using namespace std;

sql::ResultSet* Broker::execute(const string statement)
{
    try {
        stmt = connection->createStatement();
        res = stmt->executeQuery(statement);
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        throw runtime_error("");
    }

    return res;
}

void Broker::connect(const string host, const string db, const string user, const string password)
{
    try {
        driver = get_driver_instance();
        ostringstream dsn;
        dsn << "tcp://" << host << ":3306";
        connection = driver->connect(dsn.str(), user, password);
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

sql::ResultSet* Broker::prepare_and_execute( const string sql, const vector<string> args )
{
    sql::ResultSet* result;
    prep_stmt = connection->prepareStatement(sql.c_str());
    if ( args.at(0).empty() ) {
        prep_stmt->setNull(1, sql::DataType::SQLNULL);
        prep_stmt->setNull(2, sql::DataType::SQLNULL);
    }
    else {
        prep_stmt->setString(1, args.at(0));
        prep_stmt->setString(2, args.at(0));
    }
    result = prep_stmt->executeQuery();

    return result;
}

void Broker::clean()
{
    delete res;
    delete stmt;
}

Broker::~Broker()
{
    delete res;
    delete stmt;
    delete connection;
}
