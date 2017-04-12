// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Check.hpp"
#include <Types.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <memory>
#include <string>
#include <iostream>

using namespace std;
namespace pt = boost::property_tree;

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
    string attr_file_val = "";
    auto db_schema = schema->get_schema();
    for ( auto it : *db_schema ) {
        if ( it.first == "tables" ) {
            cout << "Checking tables" << endl;
            for ( auto& tbl : it.second ) {
                cout << "checking table: " << tbl.first << endl;
                for ( auto& tbl_props : tbl.second ) {
                    if ( tbl_props.first == "table_info" ) {
                        auto& tbl_info = boost::get<basic_type>( tbl_props.second );

                        for ( auto& tbl_attr : tbl_info ) {
                            cout << "  checking attribute: " << tbl_attr.first;
                            try {
                                attr_file_val = ref_schema.get<string>( "tables." + tbl.first + ".table_info." + tbl_attr.first );
                            }
                            catch ( const exception& ex ) {
                                cout << endl << "    attribute " << tbl_attr.first << " is missing in ref file" << endl;
                                continue;
                            }
                            if ( tbl_attr.second == attr_file_val ) {
                                cout << " Equal: " << attr_file_val << endl;
                            }
                            else {
                                cout << " Not Equal. File: " << attr_file_val << " Schema: " << tbl_attr.second << endl;
                                flag = false;
                            }
                        }
                    }
                }
            }
        }
    }

    return flag;
}
