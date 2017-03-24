// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <mysql.h>
#include <string>

using namespace std;
namespace broker
{

class Broker
{
public:
    ~Broker();
    MYSQL_RES* execute(string statement);

    void connect(string host, string m_socket, string db, string user, string password);

private:
    MYSQL *connection, mysql;
    MYSQL_RES* result;

    int query_state;
};
}
