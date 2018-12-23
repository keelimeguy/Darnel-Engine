cmake_minimum_required( VERSION 3.13.2 )

# # we have a submodule setup for imgui now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- imgui
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/imgui
# )
# # we have a submodule setup for glfw now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- glfw
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

add_subdirectory( glfw EXCLUDE_FROM_ALL )
add_subdirectory( glew EXCLUDE_FROM_ALL )
add_subdirectory( stb_image EXCLUDE_FROM_ALL )

option ( IMGUI_OPENGL3_ENABLE "Imgui OpenGL3 implementation" ON )
option ( IMGUI_GLFW_ENABLE "Imgui GLFW implementation" ON )
option ( OPENGL3_GLEW_ENABLE "OpenGL3 GLEW implementation" ON )
add_subdirectory( imgui EXCLUDE_FROM_ALL )

option ( GLM_STATIC_LIBRARY_ENABLE "GLM static library" ON )
option ( GLM_STATIC_LIBRARY_ENABLE "GLM shared library" OFF )
add_subdirectory( glm EXCLUDE_FROM_ALL )
