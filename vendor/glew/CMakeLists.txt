cmake_minimum_required( VERSION 3.13.2 )

execute_process( COMMAND git submodule update --init glew
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

if ( GLEW_MAKE_WORKAROUND_ENABLE )
    execute_process( COMMAND make registry
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/auto
    )
    execute_process( COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
endif()

execute_process( COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/auto
)

if ( GLEW_GLEW_C_NEWLINE_FIX_ENABLE )
    execute_process( COMMAND sed -i ":a;N;$!ba;s/\\r\", /\", /g" glew.c
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/src
    )
endif()

add_subdirectory( glew/build/cmake EXCLUDE_FROM_ALL )

set_target_properties( glew
    PROPERTIES
        FOLDER "GLEW"
)

set_target_properties( glew_s
    PROPERTIES
        FOLDER "GLEW"
)
