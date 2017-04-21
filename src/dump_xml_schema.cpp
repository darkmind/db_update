// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <boost/program_options.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Core.hpp"
#include "Types.hpp"
#include "utils/XML_Walker.hpp"


using namespace std;
namespace po = boost::program_options;
namespace pt = boost::property_tree;


int main( int ac, char* av[] )
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")
        ("host", po::value<string>()->default_value("localhost"), "hostname to connect")
        ("db", po::value<string>()->default_value("test"), "name of the schema")
        ("user", po::value<string>()->default_value("root"), "db user")
        ("pass", po::value<string>()->default_value(""), "db password")
        ("table_name", po::value<string>()->default_value(""), "get schema of table")
        ("source_file", po::value<string>()->default_value("schema.xml"), "xml file to write schema");
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

    const unordered_map<string, string> options = {
        {"host", vm["host"].as<string>()},
        {"user", vm["user"].as<string>()},
        {"pass", vm["pass"].as<string>()},
        {"db", vm["db"].as<string>()},
    };

    shared_ptr<Core> core = shared_ptr<Core>( new Core(options) );
    core->get_schema( vm["table_name"].as<string>() );
    const shared_ptr<schema_type> schema = core->get_schema_ref()->get_schema();

    pt::ptree xml_schema;
    XML_Walker::populate_schema( schema, xml_schema );

    try {
        pt::write_xml(
            vm["source_file"].as<string>(),
            xml_schema,
            std::locale(),
            pt::xml_writer_make_settings<string>( ' ', 2 )
        );
    }
    catch ( const exception& ex ) {
        cout << "# ERR: Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << ex.what();
        throw runtime_error("");
    }

    return 0;
}
