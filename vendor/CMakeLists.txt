cmake_minimum_required( VERSION 3.13.2 )

find_library( GLEW_LIBRARY_RELEASE NAMES GLEW libglew32 glew32 glew glew32s HINTS "${CMAKE_CURRENT_LIST_DIR}/glew/bin" )
find_library( GLFW_LIBRARY_RELEASE NAMES glfw3 glfw32 glfw glfw32s HINTS "${CMAKE_CURRENT_LIST_DIR}/glfw/bin" )
find_library( STB_LIBRARY_RELEASE NAMES stb_image HINTS "${CMAKE_CURRENT_LIST_DIR}/stb/bin" )
find_library( GLM_LIBRARY_RELEASE NAMES glm_static HINTS "${CMAKE_CURRENT_LIST_DIR}/glm/bin" )

if( DX12_GLOBAL_ENABLE )
    add_subdirectory( DirectXTex EXCLUDE_FROM_ALL )
    add_subdirectory( DX12Lib EXCLUDE_FROM_ALL )
endif()

add_subdirectory( stb EXCLUDE_FROM_ALL )
add_subdirectory( glm )

if( OPENGL3_GLFW_ENABLE )
    add_subdirectory( glfw )
endif()
if( OPENGL3_GLEW_ENABLE )
    add_subdirectory( glew )
endif()
add_subdirectory( imgui EXCLUDE_FROM_ALL )
