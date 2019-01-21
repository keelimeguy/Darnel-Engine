cmake_minimum_required( VERSION 3.13.2 )

if( NOT ${GLFW_LIBRARY_RELEASE} MATCHES "GLFW_LIBRARY_RELEASE-NOTFOUND" )
    add_library( glfw INTERFACE )
    target_include_directories( glfw
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bin/include
    )

    get_filename_component( ITEM_PATH ${GLFW_LIBRARY_RELEASE} DIRECTORY )
    get_filename_component( ITEM_NAME ${GLFW_LIBRARY_RELEASE} NAME )

    target_link_libraries( glfw
        INTERFACE ${GLFW_LIBRARY_RELEASE}
    )

else()
    execute_process( COMMAND git submodule update --init glfw
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    add_subdirectory( glfw EXCLUDE_FROM_ALL )

    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    file( COPY ${CMAKE_CURRENT_LIST_DIR}/glfw/include DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin/ )

    add_custom_command( OUTPUT ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${CMAKE_CURRENT_LIST_DIR}/bin/
        COMMAND touch ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        DEPENDS glfw
    )
    add_custom_target( glfw_copy_files ALL
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
    )

endif()
