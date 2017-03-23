cmake_minimum_required(VERSION 2.8)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

project(dbup_cpp)

set( CMAKE_CXX_FLAGS "-W -Wall -Wextra -fpic -pipe -O2")
set( CMAKE_CXX_FLAGS_DEBUG "-W -Wall -Wextra -ggdb -fPIC -pipe -fstack-protector-all")

find_package( Boost COMPONENTS program_options REQUIRED )

set( MYSQL_MIN_VER 5.0 )
find_package( MySQL ${MYSQL_MIN_VER} REQUIRED )
include_directories(${MYSQL_INCLUDE_DIR})

add_executable(main test.cpp)
target_link_libraries( main ${Boost_LIBRARIES} )
target_link_libraries( main ${MYSQL_LIBRARIES} )
