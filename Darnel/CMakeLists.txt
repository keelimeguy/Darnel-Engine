cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

set( HEADER_FILES
    include/CoreFramework.h
    include/Darnel.h
    include/Sprite.h
    include/SpriteSheet.h
    include/Texture.h
    include/Window.h
    include/Event.h
    include/ApplicationEvent.h
    include/KeyEvent.h
    include/MouseEvent.h
    include/WindowEvent.h
)

set( SRC_FILES
    src/Darnel.cpp
    src/SpriteSheet.cpp
)

set( DIRECTX12_HEADER_FILES
    include/DirectX12/DirectX12Framework.h
    include/DirectX12/DirectX12Window.h
    include/DirectX12/DirectX12Renderer.h
)
set( DIRECTX12_SRC_FILES
    src/DirectX12/DirectX12Framework.cpp
    src/DirectX12/DirectX12Window.cpp
    src/DirectX12/DirectX12Renderer.cpp
)

set( OPENGL3_HEADER_FILES
    include/OpenGL3/OpenGL3Framework.h
    include/OpenGL3/OpenGL3Window.h
    include/OpenGL3/IndexBuffer.h
    include/OpenGL3/OpenGL3Renderer.h
    include/OpenGL3/OpenGL3Shader.h
    include/OpenGL3/OpenGL3Sprite.h
    include/OpenGL3/OpenGL3Texture.h
    include/OpenGL3/VertexArray.h
    include/OpenGL3/VertexBuffer.h
    include/OpenGL3/VertexBufferLayout.h
)
set( OPENGL3_SRC_FILES
    src/OpenGL3/OpenGL3Framework.cpp
    src/OpenGL3/OpenGL3Window.cpp
    src/OpenGL3/IndexBuffer.cpp
    src/OpenGL3/OpenGL3Renderer.cpp
    src/OpenGL3/OpenGL3Shader.cpp
    src/OpenGL3/OpenGL3Sprite.cpp
    src/OpenGL3/OpenGL3Texture.cpp
    src/OpenGL3/VertexArray.cpp
    src/OpenGL3/VertexBuffer.cpp
    src/OpenGL3/VertexBufferLayout.cpp
)

source_group( TREE ${CMAKE_CURRENT_LIST_DIR}/src PREFIX "Source Files"
    FILES
        ${SRC_FILES}
        ${DIRECTX12_SRC_FILES}
        ${OPENGL3_SRC_FILES}
)

source_group( TREE ${CMAKE_CURRENT_LIST_DIR}/include PREFIX "Header Files"
    FILES
        ${HEADER_FILES}
        ${DIRECTX12_HEADER_FILES}
        ${OPENGL3_HEADER_FILES}
)

if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    target_include_directories( darnel
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include
            ${CMAKE_CURRENT_LIST_DIR}/include/DirectX12
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/include/OpenGL3
    )

    target_sources( darnel
        PRIVATE
            ${HEADER_FILES}
            ${SRC_FILES}
            ${OPENGL3_HEADER_FILES}
            ${OPENGL3_SRC_FILES}
            ${DIRECTX12_HEADER_FILES}
            ${DIRECTX12_SRC_FILES}
    )
else()
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
endif()

get_target_property( DARNEL_INCLUDE darnel INCLUDE_DIRECTORIES )
get_target_property( DARNEL_INTERFACE_INCLUDE darnel INTERFACE_INCLUDE_DIRECTORIES )
get_target_property( GLM_INCLUDE glm_static INCLUDE_DIRECTORIES )
get_target_property( IMGUI_INCLUDE imgui INTERFACE_INCLUDE_DIRECTORIES )

list( APPEND DARNEL_INCLUDE ${GLM_INCLUDE} )
list( APPEND DARNEL_INTERFACE_INCLUDE ${GLM_INCLUDE} )
list( APPEND DARNEL_INTERFACE_INCLUDE ${IMGUI_INCLUDE} )

set_target_properties( darnel
    PROPERTIES
        INCLUDE_DIRECTORIES "${DARNEL_INCLUDE}"
)
set_target_properties( darnel
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${DARNEL_INTERFACE_INCLUDE}"
)

source_group( "Imgui Files" FILES ${IMGUI_SOURCE_LIST} )

target_link_libraries( darnel
    PRIVATE
        imgui
        stb_image
        glm_static
)
