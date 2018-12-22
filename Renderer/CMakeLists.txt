cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

target_sources( darnel
    PRIVATE
        src/Renderer.cpp
        include/Renderer.h
)

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( darnel
    PUBLIC
        imgui
)
