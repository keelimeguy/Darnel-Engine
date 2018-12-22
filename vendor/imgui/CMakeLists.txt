cmake_minimum_required( VERSION 3.13.2 )

set( IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui
    CACHE PATH "imgui include directory"
)

add_library( imgui INTERFACE )

target_include_directories( imgui
    INTERFACE
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}/examples
        ${CMAKE_CURRENT_LIST_DIR}/../glfw/include
)

target_link_libraries( imgui
    INTERFACE
        glfw
        glew
)

target_sources( imgui
    INTERFACE
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/examples/imgui_impl_opengl3.cpp
        imgui/examples/imgui_impl_glfw.cpp
)

target_compile_definitions( imgui
    INTERFACE
        GLFW_EXPOSE_NATIVE_WGL
        IMGUI_IMPL_OPENGL_LOADER_GLEW
)

