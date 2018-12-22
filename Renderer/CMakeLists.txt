cmake_minimum_required( VERSION 3.13.2 )

add_library( darnel STATIC "" )

target_sources( darnel
    PRIVATE
        src/IndexBuffer.cpp
        src/Renderer.cpp
        src/Shader.cpp
        src/VertexArray.cpp
        src/VertexBuffer.cpp
        src/VertexBufferLayout.cpp
        include/IndexBuffer.h
        include/Renderer.h
        include/Shader.h
        include/VertexArray.h
        include/VertexBuffer.h
        include/VertexBufferLayout.h
)

target_include_directories( darnel
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( darnel
    PUBLIC
        imgui
        glm_static
)
