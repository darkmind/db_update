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

set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
set( CMAKE_CXX_FLAGS_RELEASE "-W -Wall -Wextra -fpic -pipe -O2 -std=c++14 -s")
set( CMAKE_CXX_FLAGS_DEBUG "-W -Wall -Wextra -ggdb -fPIC -pipe -fstack-protector-all -std=c++14")

set(DB_UPDATE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package( Boost COMPONENTS program_options REQUIRED )

include_directories(
    ${DB_UPDATE_SRC}
    ${Boost_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
)

set(DB_UPDATE_SOURCE
    ${DB_UPDATE_SRC}/DB/Broker.cpp
    ${DB_UPDATE_SRC}/IO/IO.cpp
    ${DB_UPDATE_SRC}/Core.cpp
    ${DB_UPDATE_SRC}/main.cpp
)

add_executable (main ${DB_UPDATE_SOURCE})
target_link_libraries( main ${Boost_LIBRARIES} )
target_link_libraries( main /usr/lib/libmysqlcppconn.so )
