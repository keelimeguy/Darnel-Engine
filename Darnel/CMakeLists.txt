cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel SHARED "" )

set( HEADER_FILES
    include/CoreFramework.h
    include/Darnel.h
    include/Sprite.h
    include/SpriteSheet.h
    include/Texture.h
    include/Window.h
)

set( OPENGL3_HEADER_FILES
    include/OpenGL3/OpenGL3Framework.h
    include/OpenGL3/OpenGL3Window.h
    include/OpenGL3/IndexBuffer.h
    include/OpenGL3/OpenGL3Renderer.h
    include/OpenGL3/OpenGL3Shader.h
    include/OpenGL3/OpenGL3Texture.h
    include/OpenGL3/VertexArray.h
    include/OpenGL3/VertexBuffer.h
    include/OpenGL3/VertexBufferLayout.h
)

set( SRC_FILES
    src/Darnel.cpp
    src/Sprite.cpp
    src/SpriteSheet.cpp
    src/Texture.cpp
)

set( OPENGL3_SRC_FILES
    src/OpenGL3/OpenGL3Framework.cpp
    src/OpenGL3/OpenGL3Window.cpp
    src/OpenGL3/IndexBuffer.cpp
    src/OpenGL3/OpenGL3Renderer.cpp
    src/OpenGL3/OpenGL3Shader.cpp
    src/OpenGL3/OpenGL3Texture.cpp
    src/OpenGL3/VertexArray.cpp
    src/OpenGL3/VertexBuffer.cpp
    src/OpenGL3/VertexBufferLayout.cpp
)

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/OpenGL3
)

target_sources( darnel
    PRIVATE
        ${HEADER_FILES}
        ${SRC_FILES}
        ${OPENGL3_HEADER_FILES}
        ${OPENGL3_SRC_FILES}
)

get_target_property( DARNEL_INCLUDE darnel INCLUDE_DIRECTORIES )
get_target_property( STB_IMAGE_INCLUDE stb_image INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLM_INCLUDE glm_static INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND DARNEL_INCLUDE ${STB_IMAGE_INCLUDE} )
list( APPEND DARNEL_INCLUDE ${GLM_INCLUDE} )
list( APPEND DARNEL_INCLUDE ${IMGUI_INCLUDE} )

set_target_properties( darnel
    PROPERTIES
        INCLUDE_DIRECTORIES "${DARNEL_INCLUDE}"
)

get_target_property( DARNEL_INTERFACE_INCLUDE darnel INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND DARNEL_INTERFACE_INCLUDE ${GLM_INCLUDE} )
list( APPEND DARNEL_INTERFACE_INCLUDE ${IMGUI_INCLUDE} )

set_target_properties( darnel
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DARNEL_INTERFACE_INCLUDE}"
)

source_group( "Imgui Files" FILES ${IMGUI_SOURCE_LIST} )
source_group( TREE ${GLEW_INCLUDE_DIR} PREFIX "GLEW Files" FILES ${GLEW_SOURCE_LIST} )
source_group( "STB_Image Files" FILES ${STB_IMAGE_SOURCE_LIST} )

target_link_libraries( darnel
    PRIVATE
        imgui
        stb_image
        glm_static
)
