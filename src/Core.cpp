// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Core.hpp>
#include <DB/Broker.hpp>
#include <array>
#include <map>
#include <memory>
#include <mysql.h>
#include <vector>

using namespace core;
using namespace std;

Core::Core(map<string, string> options)
{
    broker = new Broker();
    broker->connect(options.at("host"), options.at("socket"), options.at("db"), options.at("user"),
        options.at("pass"));
}

vector<vector<string> > Core::execute(string query)
{
    MYSQL_RES* result = broker->execute(query);
    unsigned int c_num = mysql_num_fields(result);
    MYSQL_ROW row;
    vector<vector<string> > records;
    while((row = mysql_fetch_row(result)) != NULL) {
        vector<string> record_row;
        for(unsigned int i = 0; i <= (c_num - 1); i++) {
            if(row[i] == NULL) {
                record_row.push_back("NULL");
            } else {
                record_row.push_back(row[i]);
            }
        }
        records.push_back(record_row);
    }

    return records;
}