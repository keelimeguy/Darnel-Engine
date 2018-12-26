cmake_minimum_required( VERSION 3.13.2 )

execute_process( COMMAND git submodule update --init stb
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

add_library( stb_image STATIC "" )
set_target_properties( stb_image
    PROPERTIES
        FOLDER "STB"
)

target_include_directories( stb_image
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/stb
)

target_sources( stb_image
    PRIVATE
        stb/stb_image.h
        stb_image.cpp
)
