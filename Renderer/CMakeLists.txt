cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( darnel
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

get_target_property( DARNEL_INCLUDE darnel INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( STB_IMAGE_INCLUDE stb_image INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLM_INCLUDE glm_static INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND DARNEL_INCLUDE ${IMGUI_INCLUDE} )
list( APPEND DARNEL_INCLUDE ${STB_IMAGE_INCLUDE} )
list( APPEND DARNEL_INCLUDE ${GLM_INCLUDE} )

set_target_properties( darnel
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DARNEL_INCLUDE}"
)

target_link_libraries( darnel
    PRIVATE
        imgui
        stb_image
        glm_static
)
