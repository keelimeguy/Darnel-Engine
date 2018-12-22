cmake_minimum_required( VERSION 3.13.2 )

add_executable( test_darnel WIN32 "" )

target_sources( test_darnel
    PRIVATE
        src/Application.cpp
        src/Test.cpp
        src/TestClearColor.cpp
        include/TestClearColor.h
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
endif()

# file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
