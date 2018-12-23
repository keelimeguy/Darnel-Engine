cmake_minimum_required( VERSION 3.13.2 )

set( IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui
    CACHE PATH "imgui include directory"
)

set( IMGUI_IMPL_INCLUDE_DIR ${IMGUI_INCLUDE_DIR}/examples )
set( IMGUI_IMPL_SOURCE_LIST "" )
set( IMGUI_IMPL_LIBRARY "" )
set( IMGUI_IMPL_COMPILE_DEF "" )

if( IMGUI_OPENGL3_ENABLE )
    list( APPEND IMGUI_IMPL_SOURCE_LIST
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.h
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.cpp
    )

    if( OPENGL3_GLEW_ENABLE )
        list( APPEND IMGUI_IMPL_LIBRARY glew )
        list( APPEND IMGUI_IMPL_COMPILE_DEF IMGUI_IMPL_OPENGL_LOADER_GLEW )
    endif()

endif()

if( IMGUI_GLFW_ENABLE )
    list( APPEND IMGUI_IMPL_INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/../glfw/include
    )
    list( APPEND IMGUI_IMPL_SOURCE_LIST
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.h
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.cpp
    )
    list( APPEND IMGUI_IMPL_LIBRARY glfw )
    list( APPEND IMGUI_IMPL_COMPILE_DEF GLFW_EXPOSE_NATIVE_WGL )
endif()

if( IMGUI_WIN32_ENABLE )
    list( APPEND IMGUI_IMPL_SOURCE_LIST
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_win32.h
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_win32.cpp
    )
endif()

if( IMGUI_DX12_ENABLE )
    list( APPEND IMGUI_IMPL_SOURCE_LIST
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_dx12.h
        ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_dx12.cpp
    )
endif()

set( IMGUI_SOURCE_LIST
    ${IMGUI_INCLUDE_DIR}/imgui.h
    ${IMGUI_INCLUDE_DIR}/imgui_internal.h
    ${IMGUI_INCLUDE_DIR}/imgui.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_draw.cpp
    ${IMGUI_INCLUDE_DIR}/imgui_widgets.cpp
    ${IMGUI_IMPL_SOURCE_LIST}
    CACHE PATH "imgui source list"
)

add_library( imgui INTERFACE )

target_include_directories( imgui
    INTERFACE
        ${IMGUI_INCLUDE_DIR}
        ${IMGUI_IMPL_INCLUDE_DIR}
)

target_sources( imgui
    INTERFACE
        ${IMGUI_SOURCE_LIST}
)

if( IMGUI_OPENGL3_ENABLE AND OPENGL3_GLEW_ENABLE )
    get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )
    get_target_property( GLEW_INCLUDE glew INTERFACE_INCLUDE_DIRECTORIES )

    list( APPEND IMGUI_INCLUDE ${GLEW_INCLUDE} )

    set_target_properties( imgui
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${IMGUI_INCLUDE}"
    )
endif()

target_link_libraries( imgui
    INTERFACE
        ${IMGUI_IMPL_LIBRARY}
)

target_compile_definitions( imgui
    INTERFACE
        ${IMGUI_IMPL_COMPILE_DEF}
)
