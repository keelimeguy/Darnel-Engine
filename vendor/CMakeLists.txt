cmake_minimum_required( VERSION 3.13.2 )

# # we have a submodule setup for imgui now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- imgui
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )
# # we have a submodule setup for imgui now we need to clone this submodule
# execute_process( COMMAND git submodule update --init -- imgui
#                 WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
# )

add_subdirectory( glfw EXCLUDE_FROM_ALL )
add_subdirectory( glew EXCLUDE_FROM_ALL )
add_subdirectory( imgui EXCLUDE_FROM_ALL )

option ( GLM_STATIC_LIBRARY_ENABLE "GLM static library" ON )
add_subdirectory( glm EXCLUDE_FROM_ALL )
