cmake_minimum_required( VERSION 3.13.2 )

# # we have a submodule setup for imgui now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- imgui
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/imgui
# )
# # we have a submodule setup for glfw now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- glfw
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    add_subdirectory( DirectXTex EXCLUDE_FROM_ALL )
    add_subdirectory( DX12Lib EXCLUDE_FROM_ALL )
endif()

add_subdirectory( stb_image EXCLUDE_FROM_ALL )

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
