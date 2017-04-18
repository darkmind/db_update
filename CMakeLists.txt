cmake_minimum_required(VERSION 2.8)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

project(db_update)

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release )
endif()

string( TOLOWER "${CMAKE_BUILD_TYPE}" STR_TOLOWER )

if( STR_TOLOWER STREQUAL release )
    set( CMAKE_BUILD_TYPE Release)
elseif( STR_TOLOWER STREQUAL debug )
    set( CMAKE_BUILD_TYPE Debug)
else()
    message( FATAL_ERROR "Incorrect type of build" )
endif()

set( CMAKE_CXX_COMPILER "clang++-4.0" )
set( CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++14 -pipe")
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -flto")
set( CMAKE_CXX_FLAGS_DEBUG "-O0 -glldb -fstack-protector-all")

set( CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld -pie" )
set( CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" )
set( CMAKE_EXE_LINKER_FLAGS_DEBUG "" )

set(DB_UPDATE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package( Boost COMPONENTS program_options REQUIRED )
find_package( Mysql-Connector-C++ REQUIRED )

include_directories(
    ${DB_UPDATE_SRC}
    ${Boost_INCLUDE_DIRS}
    ${MYSQLCONNECTORCPP_INCLUDE_DIR}
)

set(DB_UPDATE_SOURCE
    ${DB_UPDATE_SRC}/DB/Broker.cpp
    ${DB_UPDATE_SRC}/DB/Schema.cpp
    ${DB_UPDATE_SRC}/DB/Schema_Walker.cpp
    ${DB_UPDATE_SRC}/IO/IO.cpp
    ${DB_UPDATE_SRC}/Core.cpp
    ${DB_UPDATE_SRC}/Stages/Check.cpp
    ${DB_UPDATE_SRC}/main.cpp
)

add_executable (db_update ${DB_UPDATE_SOURCE})
target_link_libraries( db_update ${Boost_LIBRARIES} )
target_link_libraries( db_update ${MYSQLCONNECTORCPP_LIBRARIES} )
