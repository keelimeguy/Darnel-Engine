cmake_minimum_required( VERSION 3.13.2 )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project( Darnel LANGUAGES CXX C )

option ( GLEW_MAKE_WORKAROUND_ENABLE "When making GLEW/auto, perform `make ext` separately" ON )
option ( GLEW_GLEW_C_NEWLINE_FIX_ENABLE "After making GLEW/auto, fix newline issues within strings in glew.c" ON )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    option ( IMGUI_WIN32_ENABLE "Imgui Win32 implementation" ON )
    option ( IMGUI_DX12_ENABLE "Imgui DirectX12 implementation" ON )
else()
    option ( IMGUI_WIN32_ENABLE "Imgui Win32 implementation" OFF )
    option ( IMGUI_DX12_ENABLE "Imgui DirectX12 implementation" OFF )
endif()

option ( IMGUI_OPENGL3_ENABLE "Imgui OpenGL3 implementation" ON )
option ( OPENGL3_GLEW_ENABLE "OpenGL3 GLEW implementation" ON )
option ( IMGUI_GLFW_ENABLE "Imgui GLFW implementation" ON )
option ( GLM_STATIC_LIBRARY_ENABLE "GLM static library" ON )
option ( GLM_DYNAMIC_LIBRARY_ENABLE "GLM shared library" OFF )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)


add_subdirectory( vendor EXCLUDE_FROM_ALL )

add_subdirectory( Darnel )
add_subdirectory( Tests )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    # add_subdirectory( SampleDX12 )
    set_directory_properties( PROPERTIES
        VS_STARTUP_PROJECT test_darneldx12
    )
endif()
