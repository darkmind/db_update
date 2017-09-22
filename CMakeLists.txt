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
set( CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++14")
set( CMAKE_CXX_FLAGS_RELEASE "-O2 -flto")
set( CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set( CMAKE_EXE_LINKER_FLAGS "-fuse-ld=lld" )
set( CMAKE_EXE_LINKER_FLAGS_RELEASE "-pie -s" )
set( CMAKE_EXE_LINKER_FLAGS_DEBUG "" )

set(DB_UPDATE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package( Boost COMPONENTS program_options REQUIRED )
find_package( Mysql-Connector-C++ REQUIRED )

include_directories(
    ${DB_UPDATE_SRC}
    ${Boost_INCLUDE_DIRS}
    ${MYSQLCONNECTORCPP_INCLUDE_DIR}
)

set( DB_UPDATE_SOURCE
    ${DB_UPDATE_SRC}/main.cpp
    ${DB_UPDATE_SRC}/Core.cpp
    ${DB_UPDATE_SRC}/Stage/Check.cpp
    ${DB_UPDATE_SRC}/Schema.cpp
    ${DB_UPDATE_SRC}/Schema/DB/IO.cpp
    ${DB_UPDATE_SRC}/Schema/DB/Broker.cpp
    ${DB_UPDATE_SRC}/Schema/File/XML_Handler.cpp
    ${DB_UPDATE_SRC}/Schema/Tree/Tree.cpp
    ${DB_UPDATE_SRC}/Schema/Tree/Node.cpp
)

add_executable ( ${CMAKE_PROJECT_NAME} ${DB_UPDATE_SOURCE} )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${MYSQLCONNECTORCPP_LIBRARIES} )
