// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Core.hpp>
#include <DB/Broker.hpp>
#include <map>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <vector>

using namespace std;
using namespace core;
using namespace broker;

Core::Core(map<string, string> options)
{
    broker = new Broker();
    broker->connect(options.at("host"), options.at("db"), options.at("user"), options.at("pass"));
}

vector<vector<string> > Core::execute(string statement)
{
    sql::ResultSet* result = broker->execute(statement);
    sql::ResultSetMetaData *res_meta = result->getMetaData();
    unsigned int c_num = res_meta->getColumnCount();
    vector<vector<string> > records;
    while (result->next()) {
        vector<string> record_row;
        for(unsigned int i = 1; i <= c_num; i++) {
            if(result->isNull(i)) {
                record_row.push_back("NULL");
            } else {
                record_row.push_back(result->getString(i));
            }
        }
        records.push_back(record_row);
    }
    broker->clean();

    return records;
}