# - Try to find Mysql-Connector-C++
#  MYSQLCONNECTORCPP_FOUND - Mysql-Connector-C++ installed
#  MYSQLCONNECTORCPP_INCLUDE_DIRS - Mysql-Connector-C++ include directories
#  MYSQLCONNECTORCPP_LIBRARIES - Mysql-Connector-C++ libs

set(MYSQLCONNECTORCPP_ROOT_DIR
"${MYSQLCONNECTORCPP_ROOT_DIR}"
    CACHE
    PATH
    "Where to start looking for this component.")

find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
    mysql_connection.h
    HINTS
    ${MYSQLCONNECTORCPP_ROOT_DIR}
    PATH_SUFFIXES
    include)

find_library(MYSQLCONNECTORCPP_LIBRARY
    NAMES
    mysqlcppconn
    mysqlcppconn-static
    HINTS
    ${MYSQLCONNECTORCPP_ROOT_DIR}
    PATH_SUFFIXES
    lib64
    lib)

mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR MYSQLCONNECTORCPP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MysqlConnectorCpp
    DEFAULT_MSG
    MYSQLCONNECTORCPP_INCLUDE_DIR
    MYSQLCONNECTORCPP_LIBRARY)

if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS "${MYSQLCONNECTORCPP_INCLUDE_DIR}")
    set(MYSQLCONNECTORCPP_LIBRARIES "${MYSQLCONNECTORCPP_LIBRARY}")
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
endif()

