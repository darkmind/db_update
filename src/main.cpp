// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Core.hpp>
#include <DB/Broker.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
namespace po = boost::program_options;
using namespace broker;

int main(int ac, char* av[])
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")
        ("host", po::value<string>()->default_value("localhost"), "hostname to connect")
        ("socket", po::value<string>()->default_value("/tmp/mysql.sock"), "socket to connect")
        ("db", po::value<string>()->default_value("test"), "name of the schema")
        ("user", po::value<string>()->default_value("root"), "db user")
        ("pass", po::value<string>()->default_value(""), "db password")
        ("query", po::value<string>()->default_value("select 1 from dual"), "query to run");
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(ac, av, desc), vm);
    } catch(const std::exception& e) {
        cout << "Can't parse passed parameters" << endl;
        cout << e.what() << endl;
        return 0;
    }
    po::notify(vm);

    if(vm.count("help")) {
        cout << desc << endl;
        return 1;
    }

    map<string, string> options = {
        {"host", vm["host"].as<string>()}, {"user", vm["user"].as<string>()},
        {"pass", vm["pass"].as<string>()}, {"socket", vm["socket"].as<string>()},
        {"db", vm["db"].as<string>()},
    };

    core::Core* core = new core::Core(options);
    vector<vector<string>> records = core->execute(vm["query"].as<string>());
    for(auto& row : records) {
        for(auto& val : row) {
            cout << "'" << val << "' ";
        }
        cout << endl;
    }
}
