cmake_minimum_required( VERSION 3.13.2 )

execute_process( COMMAND git submodule update --init glfw
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory( glfw EXCLUDE_FROM_ALL )
