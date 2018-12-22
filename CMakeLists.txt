cmake_minimum_required( VERSION 3.13.2 )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project( Darnel LANGUAGES CXX C )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # Output directory for static lib (.LIB)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for shared lib (.DLL)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # Output directory for executables (.EXE)

add_subdirectory( vendor )
add_subdirectory( Renderer )
add_subdirectory( Tests )

set_directory_properties( PROPERTIES
    VS_STARTUP_PROJECT test_darnel
)
