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

using namespace std;
using namespace broker;

sql::ResultSet* Broker::execute(string statement)
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

void Broker::connect(string host, string db, string user, string password)
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

vector<vector<string> > Broker::prepare_and_execute( string sql, std::vector<std::string> args )
{
    sql::PreparedStatement *prep_stmt = connection->prepareStatement(sql.c_str());
    
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
