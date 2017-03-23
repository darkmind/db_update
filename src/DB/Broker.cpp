// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <sstream>
#include <mysql.h>
#include "DB/Broker.hpp"

using namespace std;

using namespace broker;
MYSQL_RES*
Broker::execute(string statement) {
    query_state = mysql_query(connection, statement.c_str());
    if ( query_state != 0 )  {
        std::ostringstream out;
        out << "Query preparation failed: " << mysql_error(connection);
        throw runtime_error(out.str());
    }

    result = mysql_store_result(connection);
    if ( result == 0 )  {
        std::ostringstream out;
        out << "Query run failed: " << mysql_error(connection);
        throw runtime_error(out.str());
    }

    return result;
}

void
Broker::connect( string host, string m_socket, string db, string user, string password ) {
    mysql_init(&mysql);

    connection = mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(),
        db.c_str(), 3306, m_socket.c_str(), 0);
    if ( connection == 0 ) {
        std::ostringstream out;
        out << "Can't connect to db: " << mysql_error(connection);
        throw runtime_error(out.str());
    }
}

Broker::~Broker () {
    mysql_close(connection);
}
