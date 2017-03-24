cmake_minimum_required(VERSION 2.8)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

project(db_update)

set( CMAKE_CXX_FLAGS "-W -Wall -Wextra -fpic -pipe -O2 -std=c++14")
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
    ${DB_UPDATE_SRC}/Core.cpp
    ${DB_UPDATE_SRC}/main.cpp
)

add_executable (main ${DB_UPDATE_SOURCE})
target_link_libraries( main ${Boost_LIBRARIES} )
target_link_libraries( main /usr/lib/libmysqlcppconn.so )
