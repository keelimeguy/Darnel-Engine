cmake_minimum_required( VERSION 3.17.2 )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

project( Darnel VERSION 0.0.1 LANGUAGES CXX C )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    option( WINDOWS_VS "Using Windows Visual Studio" ON )
else()
    option( WINDOWS_VS "Using Windows Visual Studio" OFF )
endif()

if( DX12_GLOBAL_ENABLE )
    if( NOT WINDOWS_VS )
        message( SEND_ERROR "DX12 without Windows VS!" )
    endif()
    option( IMGUI_WIN32_ENABLE "Imgui Win32 implementation" ON )
    option( IMGUI_DX12_ENABLE "Imgui DirectX12 implementation" ON )
else()
    option( IMGUI_WIN32_ENABLE "Imgui Win32 implementation" OFF )
    option( IMGUI_DX12_ENABLE "Imgui DirectX12 implementation" OFF )
endif()

if( OPENGL3_GLOBAL_ENABLE )
    option( OPENGL3_GLEW_ENABLE "OpenGL3 GLEW implementation" ON )
    option( OPENGL3_GLFW_ENABLE "OpenGL3 GLFW implementation" ON )
    option( IMGUI_OPENGL3_ENABLE "Imgui OpenGL3 implementation" ON )
    option( IMGUI_GLFW_ENABLE "Imgui GLFW implementation" ON )
else()
    option( OPENGL3_GLEW_ENABLE "OpenGL3 GLEW implementation" OFF )
    option( OPENGL3_GLFW_ENABLE "OpenGL3 GLFW implementation" OFF )
    option( IMGUI_OPENGL3_ENABLE "Imgui OpenGL3 implementation" OFF )
    option( IMGUI_GLFW_ENABLE "Imgui GLFW implementation" OFF )
endif()

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib ) # Output directory for static lib (.LIB) (.A)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for shared lib (.DLL)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # Output directory for executables (.EXE)


add_subdirectory( vendor )

add_subdirectory( Darnel )
add_subdirectory( Tests )

if( WINDOWS_VS )
    if (DX12_GLOBAL_ENABLE)
        set_directory_properties( PROPERTIES
            VS_STARTUP_PROJECT test_darneldx12
        )
    else()
        set_directory_properties( PROPERTIES
            VS_STARTUP_PROJECT test_darnel
        )
    endif()
endif()
