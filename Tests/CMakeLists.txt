cmake_minimum_required( VERSION 3.13.2 )

add_executable( test_darnel WIN32 "" )

# file( GLOB_RECURSE RESOURCE_FILES resources/* )
# source_group( TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${RESOURCE_FILES} )

target_sources( test_darnel
    PRIVATE
        include/Test.h
        include/TestApp.h
        include/TestClearColor.h
        include/TestLayer.h
        src/main.cpp
        src/Test.cpp
        src/TestClearColor.cpp
)

target_include_directories( test_darnel
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( test_darnel
    PRIVATE darnel
)

# Tell Visual Studio to run through console (not as a Windows app)
if( WINDOWS_VS )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
    # file( COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
endif()

# file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
