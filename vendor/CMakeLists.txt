cmake_minimum_required( VERSION 3.13.2 )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" AND DX12_GLOBAL_ENABLE )
    add_subdirectory( DirectXTex EXCLUDE_FROM_ALL )
    add_subdirectory( DX12Lib EXCLUDE_FROM_ALL )
endif()

add_subdirectory( stb EXCLUDE_FROM_ALL )

if( IMGUI_GLFW_ENABLE )
    add_subdirectory( glfw EXCLUDE_FROM_ALL )
endif()
if( IMGUI_OPENGL3_ENABLE AND OPENGL3_GLEW_ENABLE )
    add_subdirectory( glew EXCLUDE_FROM_ALL )
endif()
add_subdirectory( imgui EXCLUDE_FROM_ALL )

if( GLM_STATIC_LIBRARY_ENABLE OR GLM_DYNAMIC_LIBRARY_ENABLE)
    add_subdirectory( glm EXCLUDE_FROM_ALL )
endif()
