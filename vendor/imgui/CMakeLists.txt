cmake_minimum_required( VERSION 3.13.2 )

set( IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui
    CACHE PATH "imgui include directory"
)

set( IMGUI_SOURCE_LIST
    ${IMGUI_INCLUDE_DIR}/imgui.h
    ${IMGUI_INCLUDE_DIR}/imgui_internal.h
    ${IMGUI_INCLUDE_DIR}/imgui.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.cpp
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.cpp
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.h
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.h
    CACHE PATH "imgui source list"
)

add_library( imgui INTERFACE )

target_include_directories( imgui
    INTERFACE
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}/examples
        ${CMAKE_CURRENT_LIST_DIR}/../glfw/include
)

target_sources( imgui
    INTERFACE
        ${IMGUI_SOURCE_LIST}
)

get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLEW_INCLUDE glew INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND IMGUI_INCLUDE ${GLEW_INCLUDE} )

set_target_properties( imgui
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${IMGUI_INCLUDE}"
)

target_link_libraries( imgui
    INTERFACE
        glfw
        glew
)

target_compile_definitions( imgui
    INTERFACE
        GLFW_EXPOSE_NATIVE_WGL
        IMGUI_IMPL_OPENGL_LOADER_GLEW
)
