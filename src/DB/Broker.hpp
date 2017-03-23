// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <sstream>
#include <mysql.h>

using namespace std;

namespace broker {

class Broker {
public:
    MYSQL_RES* execute(string statement);

    void connect( string host, string m_socket, string db, string user, string password );

    ~Broker ();

private:
    MYSQL *connection, mysql;
    MYSQL_RES *result;

    int query_state;
};

}
