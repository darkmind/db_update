// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include <memory>
#include <Types.hpp>

class Schema_Walker
{
public:
    Schema_Walker();

    ~Schema_Walker();

    static void travel_schema( const std::shared_ptr<schema_type> schema );

    template< typename T >
    static void travel( T leaf );
    static void travel( info leaf_b );
    static void travel( basic_type leaf );

private:
    static std::size_t counter;
};
