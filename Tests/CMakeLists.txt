cmake_minimum_required( VERSION 3.13.2 )

add_executable( test_darnel WIN32 "" )

file( GLOB_RECURSE RESOURCE_FILES resources/* )

source_group( TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${RESOURCE_FILES} )

target_sources( test_darnel
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

target_include_directories( test_darnel
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( test_darnel
    PUBLIC
        darnel
)

# Tell Visual Studio to run through console (not as a Windows app)
if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
    file( COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
else()
    file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
endif()

