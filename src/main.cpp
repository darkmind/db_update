// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Core.hpp"
#include "Types.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <unordered_map>
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
        ("print_schema", "print schema to output")
        ("check", "run check of schema")
        ("dump", "dump schema to json file specified in --source_file option")
        ("source_file", po::value<string>()->default_value("schema.json"), "file with json schema")
        ("query", po::value<string>()->default_value(""), "query to run")
        ("table_name", po::value<string>()->default_value(""), "get schema of table");
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

    if ( vm.count("check") and vm.count("dump") ) {
        cout << "--check and --dump are mutually excluding. Please specify the command" << endl;
        cout << desc << endl;
        return 0;
    }

    const unordered_map<string, string> options = {
        {"host", vm["host"].as<string>()},
        {"user", vm["user"].as<string>()},
        {"pass", vm["pass"].as<string>()},
        {"db", vm["db"].as<string>()},
        {"source_file", vm["source_file"].as<string>()}
    };

    Core core{options};

    if ( vm.count("dump") ) {
        core.dump_schema();
        cout << "Schema was dumped to " << vm["source_file"].as<string>() << endl;
    }

    if (! vm["query"].as<string>().empty() ) {
        const mysql_rows records = core.execute( vm["query"].as<string>() );
        for( auto& row : records ) {
            for( auto& val : row ) {
                cout << "'" << val << "' ";
            }
            cout << endl;
        }
    }

    if ( vm.count("print_schema") ) {
        core.print_schema();
    }

    if ( vm.count("check") ) {
        if ( ! core.run_check()  ) {
            cout << "Check is failed, see datails above" << endl;
            return 1;
        }
    }

    return 0;
}
