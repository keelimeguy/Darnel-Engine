cmake_minimum_required( VERSION 3.13.2 )

add_executable( test_darnel WIN32 "" )

file( GLOB_RECURSE RESOURCE_FILES resources/* )
source_group( TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${RESOURCE_FILES} )

target_sources( test_darnel
    PRIVATE
        ${RESOURCE_FILES}
        include/Test.h
        include/TestClearColor.h
        include/TestSprite.h
        include/TestSpriteSheet.h
        include/TestMultiWindow.h
        src/Test.cpp
        src/TestClearColor.cpp
        src/TestSprite.cpp
        src/TestSpriteSheet.cpp
        src/TestMultiWindow.cpp
        src/main.cpp
)

target_include_directories( test_darnel
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries( test_darnel
    PRIVATE
        darnel
)

# Tell Visual Studio to run through console (not as a Windows app)
if( CMAKE_GENERATOR MATCHES "Visual Studio*" )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE" )
    file( COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
endif()

file( COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

if( CMAKE_GENERATOR MATCHES "Visual Studio*" AND DX12_GLOBAL_ENABLE )
    add_executable( test_darneldx12 WIN32 "" )
    target_sources( test_darneldx12
        PRIVATE
            src/dx12_main.cpp
    )
    target_include_directories( test_darneldx12
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    )
    target_link_libraries( test_darneldx12
        PRIVATE
            darnel
    )
endif()
