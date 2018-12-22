cmake_minimum_required( VERSION 3.13.2 )

set( STB_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}
    CACHE PATH "stb_image include directory"
)

set( STB_IMAGE_SOURCE_LIST
    ${STB_IMAGE_INCLUDE_DIR}/stb_image.cpp
    ${STB_IMAGE_INCLUDE_DIR}/stb_image.h
    CACHE PATH "stb_image source list"
)

add_library( stb_image INTERFACE )

target_include_directories( stb_image
    INTERFACE
        ${STB_IMAGE_INCLUDE_DIR}
)

target_sources( stb_image
    INTERFACE
        ${STB_IMAGE_SOURCE_LIST}
)
