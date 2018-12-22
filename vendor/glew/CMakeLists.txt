cmake_minimum_required( VERSION 3.13.2 )

set( GLEW_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include
    CACHE PATH "glew include directory"
)

add_library( glew INTERFACE )

target_include_directories( glew INTERFACE ${GLEW_INCLUDE_DIR} )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    set( GLEW_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/x64/glew32s.lib )
else()
    set( GLEW_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/mingw64/glew32.dll )
    file( COPY ${GLEW_LIB_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
endif()

target_link_libraries( glew
    INTERFACE
        opengl32.lib
        ${GLEW_LIB_PATH}
)

target_compile_definitions( glew
    INTERFACE
        GLEW_STATIC
)
