cmake_minimum_required( VERSION 3.13.2 )

if( NOT ${STB_LIBRARY_RELEASE} MATCHES "STB_LIBRARY_RELEASE-NOTFOUND" )
    add_library( stb_image INTERFACE )
    target_include_directories( stb_image
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bin/include
    )

    get_filename_component( ITEM_PATH ${STB_LIBRARY_RELEASE} DIRECTORY )
    get_filename_component( ITEM_NAME ${STB_LIBRARY_RELEASE} NAME )

    target_link_libraries( stb_image
        INTERFACE ${STB_LIBRARY_RELEASE}
    )

else()
    execute_process( COMMAND git submodule update --init stb
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    add_library( stb_image STATIC "" )
    set_target_properties( stb_image
        PROPERTIES
            FOLDER "STB"
    )

    target_include_directories( stb_image
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/stb
    )

    target_sources( stb_image
        PRIVATE
            stb/stb_image.h
            stb_image.cpp
    )

    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/include )
    file( GLOB STB_PUBLIC_HEADERS "${CMAKE_CURRENT_LIST_DIR}/stb/*.h" )
    file( COPY ${STB_PUBLIC_HEADERS} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin/include/ )

    add_custom_command( TARGET stb_image POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:stb_image> ${CMAKE_CURRENT_LIST_DIR}/bin/
    )

endif()
