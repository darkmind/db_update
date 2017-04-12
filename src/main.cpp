// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core.hpp"
#include "Types.hpp"
#include "DB/Schema.hpp"
#include "Stages/Check.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
namespace po = boost::program_options;

int main( int ac, char* av[] )
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")
        ("host", po::value<string>()->default_value("localhost"), "hostname to connect")
        ("db", po::value<string>()->default_value("test"), "name of the schema")
        ("user", po::value<string>()->default_value("root"), "db user")
        ("pass", po::value<string>()->default_value(""), "db password")
        ("query", po::value<string>()->default_value(""), "query to run")
        ("table_name", po::value<string>()->default_value(""), "get schema of table")
        ("print_schema", "print schema to output")
        ("check", "run check of schema")
        ("source_file", po::value<string>()->default_value("schema.yml"), "file with schema ref");
    po::variables_map vm;
    try {
        po::store( po::parse_command_line(ac, av, desc), vm );
    } catch(const exception& e) {
        cout << "Can't parse passed parameters" << endl;
        cout << e.what() << endl;
        return 0;
    }
    po::notify(vm);

    if( vm.count("help") ) {
        cout << desc << endl;
        return 1;
    }

    const map<string, string> options = {
        {"host", vm["host"].as<string>()}, {"user", vm["user"].as<string>()},
        {"pass", vm["pass"].as<string>()},
        {"db", vm["db"].as<string>()},
    };

    shared_ptr<Core> core = shared_ptr<Core>( new Core(options) );
    if (! vm["query"].as<string>().empty() ) {
        const mysql_rows records = core->execute( vm["query"].as<string>() );
        for(auto& row : records) {
            for(auto& val : row) {
                cout << "'" << val << "' ";
            }
            cout << endl;
        }
    }

    core->get_schema( vm["table_name"].as<string>() );
    shared_ptr<Schema> schema = core->get_schema_ref();

    if ( vm.count("print_schema") ) {
        schema->print_schema();
    }

    if ( vm.count("check") ) {
        if ( ! Check::run( schema, vm["source_file"].as<string>() ) ) {
            cout << "Check is failed, see datails above" << endl;
            return 1;
        }
    }

    return 0;
}
