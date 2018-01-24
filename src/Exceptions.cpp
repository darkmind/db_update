// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Exceptions.hpp>

NotImplementedException::NotImplementedException() throw()
    : std::logic_error("Function not yet implemented.")
{}

char const * NotImplementedException::what() const throw()
{
    return exception::what();
}
