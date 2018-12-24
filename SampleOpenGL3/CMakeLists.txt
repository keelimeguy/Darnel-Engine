cmake_minimum_required( VERSION 3.13.2 )

add_executable( SampleOpenGL3 WIN32 "" )

set_target_properties( SampleOpenGL3
    PROPERTIES
        FOLDER "Samples"
)

file( GLOB_RECURSE RESOURCE_FILES resources/* )
source_group( TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${RESOURCE_FILES} )

target_sources( SampleOpenGL3
    PRIVATE
        ${RESOURCE_FILES}
        src/Application.cpp
        src/Test.cpp
        src/TestClearColor.cpp
        src/TestDraw.cpp
        src/TestTexture2d.cpp
        include/TestClearColor.h
        include/TestDraw.h
        include/TestTexture2d.h
    PUBLIC
        include/Test.h
)

target_include_directories( SampleOpenGL3
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( SampleOpenGL3
    PUBLIC
        OpenGL3Lib
)

# Tell Visual Studio to run through console (not as a Windows app)
if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
    file( COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
endif()

file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
