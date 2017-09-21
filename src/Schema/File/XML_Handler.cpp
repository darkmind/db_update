// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Types.hpp"
#include "XML_Handler.hpp"

#include <string>
#include <stdexcept>

using namespace std;

XML_Handler::XML_Handler()
{
}

void XML_Handler::get_table() const
{}

void XML_Handler::get_column() const
{}

void XML_Handler::get_index() const
{}

void XML_Handler::dump_schema() const
{}

mysql_rows XML_Handler::execute( const string& statement ) const {
    throw runtime_error("Can't call execute on non-db Schema");
}

void XML_Handler::read_schema()
{}

XML_Handler::~XML_Handler()
{
}

