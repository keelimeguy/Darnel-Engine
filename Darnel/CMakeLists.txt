cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel SHARED "" )

set( HEADER_FILES
    include/CoreFramework.h
    include/Darnel.h
    include/OpenGL3Framework.h
    include/OpenGL3Window.h
    include/Sprite.h
    include/SpriteSheet.h
    include/Texture.h
    include/Window.h
)

set( SRC_FILES
    src/Darnel.cpp
    src/OpenGL3Framework.cpp
    src/OpenGL3Window.cpp
    src/Sprite.cpp
    src/SpriteSheet.cpp
    src/Texture.cpp
)

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( darnel
    PRIVATE
        ${HEADER_FILES}
        ${SRC_FILES}
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
