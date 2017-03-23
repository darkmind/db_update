if( MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES )
    set( MYSQL_QUIET TRUE )
endif( MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES )

find_program( MYSQL_CONFIG mysql_config )

if( NOT MYSQL_CONFIG )
    message( FATAL_ERROR "mysql_config not found" )
endif( NOT MYSQL_CONFIG )

execute_process( COMMAND ${MYSQL_CONFIG} "--include" ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE MY_TMP )
string( REGEX REPLACE "-I([^ ]*)( .*)?" "\\1" MY_TMP "${MY_TMP}" )
set( MYSQL_ADD_INCLUDE_PATH ${MY_TMP} CACHE FILEPATH INTERNAL )

execute_process( COMMAND ${MYSQL_CONFIG} "--libs_r" ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE MY_TMP )
set( MYSQL_ADD_LIBRARIES "" )
string( REGEX MATCHALL "-l[^ ]*" MYSQL_LIB_LIST "${MY_TMP}" )

foreach( LIB ${MYSQL_LIB_LIST} )
    string( REGEX REPLACE "[ ]*-l([^ ]*)" "\\1" LIB "${LIB}" )
    list( APPEND MYSQL_ADD_LIBRARIES "${LIB}" )
endforeach( LIB ${MYSQL_LIB_LIST} )

set( MYSQL_ADD_LIBRARIES_PATH "" )
string( REGEX MATCHALL "-L[^ ]*" MYSQL_LIBDIR_LIST "${MY_TMP}" )

foreach( LIB ${MYSQL_LIBDIR_LIST} )
    string( REGEX REPLACE "[ ]*-L([^ ]*)" "\\1" LIB "${LIB}" )
    list( APPEND MYSQL_ADD_LIBRARIES_PATH "${LIB}" )
endforeach( LIB ${MYSQL_LIBS} )

find_path( MYSQL_INCLUDE_DIR NAMES mysql.h PATHS
    ${MYSQL_ADD_INCLUDE_PATH}
)

foreach( LIB ${MYSQL_ADD_LIBRARIES} )
    find_library( MYSQL_LIBRARIES NAMES ${LIB} PATHS
        ${MYSQL_ADD_LIBRARIES_PATH}
    )
endforeach( LIB ${MYSQL_ADD_LIBRARY} )

if( MYSQL_LIBRARIES )
    message( STATUS "Found MySQL libraries: ${MYSQL_LIBRARIES}" )
    if( MYSQL_INCLUDE_DIR )
        message( STATUS "Found MySQL headers: ${MYSQL_INCLUDE_DIR}/mysql.h" )
    else( MYSQL_INCLUDE_DIR )
        message( FATAL_ERROR "Could not find MySQL headers! Please install libraries and headers")
    endif( MYSQL_INCLUDE_DIR )
else( MYSQL_LIBRARIES )
    message( FATAL_ERROR "Could not find the MySQL libraries! Please install libraries and headers")
endif( MYSQL_LIBRARIES )
