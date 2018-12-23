cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( darnel
    PRIVATE
        include/Sprite.h
        include/Darnel.h
        src/Sprite.cpp
        src/Darnel.cpp
)

get_target_property( DARNEL_INCLUDE darnel INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLM_INCLUDE glm_static INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND DARNEL_INCLUDE ${GLM_INCLUDE} )
list( APPEND DARNEL_INCLUDE ${IMGUI_INCLUDE} )

set_target_properties( darnel
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DARNEL_INCLUDE}"
)

target_link_libraries( darnel
    PRIVATE
        OpenGL3Lib
)
