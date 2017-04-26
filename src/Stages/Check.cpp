// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Check.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "DB/Node.hpp"
#include <memory>
#include <string>
#include <iostream>

using namespace std;
namespace pt = boost::property_tree;

size_t Check::counter = 0;

bool Check::run( const shared_ptr<Schema> schema, const string& ref_schema_file ) {

    pt::ptree ref_schema;
    try {
        pt::read_xml( ref_schema_file, ref_schema );
    }
    catch ( const exception& ex ) {
        cout << "# ERR: Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << ex.what();
        throw runtime_error("");
    }

    bool flag = true;
    auto db_schema = schema->get_schema();
    Check::check_schema( db_schema, ref_schema, "schema", flag );

    return flag;
}

void Check::check_schema( const shared_ptr<Node> db_schema, const pt::ptree& ref_schema, const string& parent, bool& flag ) {
    string add_parent;
    cout << string( Check::counter, ' ' ) << "Checking " << db_schema->get_name() << endl;
    Check::counter++;

    if ( db_schema->has_children() ) {
        for ( auto child : db_schema->get_children() ) {
            if ( parent.empty() ) {
                add_parent = child.first;
            }
            else {
                add_parent = parent + "." + child.first;
            }
            check_schema( child.second, ref_schema, add_parent, flag );
        }
    }
    else {
        for ( auto data : db_schema->get_data() ) {
            cout << string( Check::counter, ' ' ) << "Checking " << data.first;
            add_parent = parent + "." + data.first;

            string attr_file_val;
            try {
                attr_file_val = ref_schema.get<string>(add_parent);
            }
            catch ( const exception& ex ) {
                cout << " Attribute " << add_parent << " is missing in ref file" << endl;
                flag = false;
                continue;
            }

            if ( data.second == attr_file_val ) {
                cout << " Equal: " << attr_file_val << endl;
            }
            else {
                cout << " Not Equal. File: " << attr_file_val << " Schema: " << data.second << endl;
                flag = false;
            }
        }
    }
    Check::counter--;
}
