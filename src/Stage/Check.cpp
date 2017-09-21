// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Stage/Check.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;
namespace pt = boost::property_tree;

Check::Check() :
    success(true)
{}

bool Check::run() {

    check_schema();

    return success;
}

void Check::check_schema() {
}
