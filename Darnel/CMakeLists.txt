cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

set( HEADER_FILES
    include/Application.h
    include/Core.h
    include/Darnel.h
    include/Layer.h
    include/LayerStack.h
    include/Renderer.h
    include/Window.h
    include/Event/ApplicationEvent.h
    include/Event/Event.h
    include/Event/KeyEvent.h
    include/Event/MouseEvent.h
    include/Event/WindowEvent.h
    include/Graphics2D/Entity.h
    include/Graphics2D/Sprite.h
    include/Graphics2D/SpriteSheet.h
    include/Graphics2D/Texture.h
    include/ImGui/ImGuiLayer.h
)

set( SRC_FILES
    src/Application.cpp
    src/LayerStack.cpp
    src/SpriteSheet.cpp
    src/ImGui/ImGuiLayer.cpp
)

set( DIRECTX12_HEADER_FILES
)
set( DIRECTX12_SRC_FILES
)

set( OPENGL3_HEADER_FILES
    include/OpenGL3/IndexBuffer.h
    include/OpenGL3/OpenGL3Renderer.h
    include/OpenGL3/OpenGL3Shader.h
    include/OpenGL3/OpenGL3Sprite.h
    include/OpenGL3/OpenGL3Texture.h
    include/OpenGL3/OpenGL3Window.h
    include/OpenGL3/VertexArray.h
    include/OpenGL3/VertexBuffer.h
    include/OpenGL3/VertexBufferLayout.h
)
set( OPENGL3_SRC_FILES
    src/OpenGL3/IndexBuffer.cpp
    src/OpenGL3/OpenGL3Renderer.cpp
    src/OpenGL3/OpenGL3Shader.cpp
    src/OpenGL3/OpenGL3Sprite.cpp
    src/OpenGL3/OpenGL3Texture.cpp
    src/OpenGL3/OpenGL3Window.cpp
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

if( WINDOWS_VS AND DX12_GLOBAL_ENABLE )
    target_include_directories( darnel
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include
            ${CMAKE_CURRENT_LIST_DIR}/include/Event
            ${CMAKE_CURRENT_LIST_DIR}/include/Graphics2D
            ${CMAKE_CURRENT_LIST_DIR}/include/ImGui
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/include/DirectX12
    )

    target_sources( darnel
        PRIVATE
            ${HEADER_FILES}
            ${SRC_FILES}
            ${DIRECTX12_HEADER_FILES}
            ${DIRECTX12_SRC_FILES}
    )
else()
    target_include_directories( darnel
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include
            ${CMAKE_CURRENT_LIST_DIR}/include/Event
            ${CMAKE_CURRENT_LIST_DIR}/include/Graphics2D
            ${CMAKE_CURRENT_LIST_DIR}/include/ImGui
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
get_target_property( GLM_INCLUDE glm_static INTERFACE_INCLUDE_DIRECTORIES )
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
