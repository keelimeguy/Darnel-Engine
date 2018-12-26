cmake_minimum_required( VERSION 3.13.2 )

execute_process( COMMAND git submodule update --init glm
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory( glm EXCLUDE_FROM_ALL )

set_target_properties( glm_shared
    PROPERTIES
        FOLDER "GLM"
)

set_target_properties( glm_static
    PROPERTIES
        FOLDER "GLM"
)
