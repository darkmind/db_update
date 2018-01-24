// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <stdexcept>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException() throw();

    virtual char const* what() const throw();
};
