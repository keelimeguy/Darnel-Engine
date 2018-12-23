cmake_minimum_required( VERSION 3.13.2 )

set( HEADER_FILES
    include/Camera.h
    include/Light.h
    include/Material.h
    include/SampleDX12.h
)

set( SRC_FILES
    src/Camera.cpp
    src/main.cpp
    src/Light.cpp
    src/Material.cpp
    src/SampleDX12.cpp
)

set( VERTEX_SHADER_FILES
    resources/shaders/HDR_VS.hlsl
    resources/shaders/HDRtoSDR_VS.hlsl
    resources/shaders/Skybox_VS.hlsl
)

set( PIXEL_SHADER_FILES
    resources/shaders/HDR_PS.hlsl
    resources/shaders/HDRtoSDR_PS.hlsl
    resources/shaders/Skybox_PS.hlsl
)

set( SHADER_FILES
    ${VERTEX_SHADER_FILES}
    ${PIXEL_SHADER_FILES}
)

set( TEXTURE_FILES
    resources/textures/DefaultWhite.bmp
    resources/textures/Directx9.png
    resources/textures/earth.dds
    resources/textures/Mona_Lisa.jpg
    resources/textures/grace-new.hdr
)

file( GLOB_RECURSE RESOURCE_FILES resources/* )
source_group( TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${RESOURCE_FILES} )

set_source_files_properties( ${SHADER_FILES}
    PROPERTIES
        VS_SHADER_OBJECT_FILE_NAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data/shaders/%(Filename).cso"
        VS_SHADER_MODEL 5.1
        VS_SHADER_DISABLE_OPTIMIZATIONS $<$<CONFIG:Debug>:ON>
        VS_SHADER_ENABLE_DEBUG $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:ON>
)

set_source_files_properties( ${VERTEX_SHADER_FILES}
    PROPERTIES
        VS_SHADER_TYPE Vertex
)

set_source_files_properties( ${PIXEL_SHADER_FILES}
    PROPERTIES
        VS_SHADER_TYPE Pixel
)

add_executable( SampleDX12 WIN32 )

target_sources( SampleDX12
    PRIVATE
        ${HEADER_FILES}
        ${SRC_FILES}
        ${SHADER_FILES}
        ${TEXTURE_FILES}
)

target_include_directories( SampleDX12
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( SampleDX12
    DX12Lib
    D3DCompiler.lib
    Shlwapi.lib
)

# Set debug database to enable the "Edit and Continue" feature.
target_compile_options( SampleDX12
    PRIVATE $<$<CONFIG:Debug>:/ZI>
)

# Set Local Debugger Settings (Command Arguments and Environment Variables)
set( COMMAND_ARGUMENTS "-wd \"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\"" )
configure_file( SampleDX12.vcxproj.user.in ${CMAKE_CURRENT_BINARY_DIR}/SampleDX12.vcxproj.user @ONLY )

file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
