// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <sstream>
#include <mysql.h>
#include "DB/Broker.hpp"

#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;
using namespace broker;

int main(int ac, char* av[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "produce help message")
    ("host",   po::value< string >()->default_value("localhost"), "hostname to connect")
    ("socket", po::value< string >()->default_value("/tmp/mysql.sock"), "socket to connect")
    ("db",     po::value< string >()->default_value("test"), "name of the schema")
    ("user",   po::value< string >()->default_value("root"), "db user")
    ("pass",   po::value< string >()->default_value(""), "db password")
    ("query",  po::value< string >()->default_value("select 1 from dual"), "query to run")
    ;
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(ac, av, desc), vm);
    } catch(const std::exception& e) {
        cout << "Can't parse passed parameters" << endl;
        cout << e.what() << endl;
        return 0;
    }
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    Broker* broker = new Broker();
    broker->connect( vm["host"].as<string>(), vm["socket"].as<string>(), vm["db"].as<string>(),
                     vm["user"].as<string>(), vm["pass"].as<string>() );

    MYSQL_ROW row;
    MYSQL_RES* result;
    result = broker->execute( vm["query"].as<string>() );
    unsigned int c_num = mysql_num_fields(result);
    while ( (row = mysql_fetch_row(result)) != NULL) {
        for ( unsigned int i = 0; i < (c_num - 1); i++ ) {
            if ( row[i] == NULL ) {
                cout << "NULL ";
            } else {
                cout << row[i] << " ";
            }
        }
        cout << endl;
    }
    mysql_free_result(result);
}
