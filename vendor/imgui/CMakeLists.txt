cmake_minimum_required( VERSION 3.13.2 )

set( IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui
    CACHE PATH "imgui include directory"
)

# add_library( imgui INTERFACE )
# target_include_directories( imgui INTERFACE ${IMGUI_INCLUDE_DIR} )
# target_link_libraries( imgui INTERFACE glfw )

add_executable( imgui WIN32 )

target_include_directories( imgui
    PUBLIC
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}/examples
        ${IMGUI_INCLUDE_DIR}/examples/libs/gl3w
        ${CMAKE_CURRENT_LIST_DIR}/../glfw/include
)

target_link_libraries( imgui
    glfw
    gdi32.lib
    opengl32.lib
    imm32.lib
)

target_compile_definitions( imgui
    PUBLIC
        GLFW_EXPOSE_NATIVE_WGL
)

target_sources( imgui
    PRIVATE
        imgui/imgui_internal.h
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/examples/imgui_impl_glfw.h
        imgui/examples/imgui_impl_glfw.cpp
        imgui/examples/imgui_impl_opengl3.h
        imgui/examples/imgui_impl_opengl3.cpp
        imgui/examples/example_glfw_opengl3/main.cpp
        imgui/examples/libs/gl3w/GL/gl3w.c
        imgui/examples/libs/gl3w/GL/gl3w.h
        imgui/examples/libs/gl3w/GL/glcorearb.h
)

# Tell Visual Studio to run through console (not as a Windows app)
if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()
