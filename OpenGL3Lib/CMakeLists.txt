cmake_minimum_required( VERSION 3.13.2 )

add_library( OpenGL3Lib STATIC "" )

target_include_directories( OpenGL3Lib
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( OpenGL3Lib
    PRIVATE
        src/IndexBuffer.cpp
        src/Renderer.cpp
        src/Shader.cpp
        src/Texture.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/VertexBufferLayout.cpp
        include/IndexBuffer.h
        include/Renderer.h
        include/Shader.h
        include/Texture.h
        include/VertexArray.h
        include/VertexBuffer.h
        include/VertexBufferLayout.h
)

source_group( "Imgui Files" FILES ${IMGUI_SOURCE_LIST} )
source_group( TREE ${GLEW_INCLUDE_DIR} PREFIX "GLEW Files" FILES ${GLEW_SOURCE_LIST} )
source_group( "STB_Image Files" FILES ${STB_IMAGE_SOURCE_LIST} )

get_target_property( OPENGL3LIB_INCLUDE OpenGL3Lib INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( STB_IMAGE_INCLUDE stb_image INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLM_INCLUDE glm_static INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND OPENGL3LIB_INCLUDE ${IMGUI_INCLUDE} )
list( APPEND OPENGL3LIB_INCLUDE ${STB_IMAGE_INCLUDE} )
list( APPEND OPENGL3LIB_INCLUDE ${GLM_INCLUDE} )

set_target_properties( OpenGL3Lib
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${OPENGL3LIB_INCLUDE}"
)

target_link_libraries( OpenGL3Lib
    PRIVATE
        imgui
        stb_image
        glm_static
)
