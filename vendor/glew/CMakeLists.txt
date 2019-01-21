cmake_minimum_required( VERSION 3.13.2 )

if( NOT ${GLEW_LIBRARY_RELEASE} MATCHES "GLEW_LIBRARY_RELEASE-NOTFOUND" )
    find_package (OpenGL REQUIRED)

    add_library( glew_s INTERFACE )
    target_include_directories( glew_s
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bin/include
    )

    get_filename_component( ITEM_PATH ${GLEW_LIBRARY_RELEASE} DIRECTORY )
    get_filename_component( ITEM_NAME ${GLEW_LIBRARY_RELEASE} NAME )

    target_link_libraries( glew_s
        INTERFACE
            ${GLEW_LIBRARY_RELEASE}
            ${OPENGL_LIBRARIES}
    )

else()
    execute_process( COMMAND git submodule update --init glew
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    if ( GLEW_MAKE_WORKAROUND_ENABLE )
        execute_process( COMMAND make registry
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/auto
        )
        execute_process( COMMAND make
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        )
    endif()

    execute_process( COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/auto
    )

    if ( GLEW_GLEW_C_NEWLINE_FIX_ENABLE )
        execute_process( COMMAND sed -i ":a;N;$!ba;s/\\r\", /\", /g" glew.c
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/glew/src
        )
    endif()

    add_subdirectory( glew/build/cmake EXCLUDE_FROM_ALL )

    set_target_properties( glew
        PROPERTIES
            FOLDER "GLEW"
    )

    set_target_properties( glew_s
        PROPERTIES
            FOLDER "GLEW"
    )

    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    file( COPY ${CMAKE_CURRENT_LIST_DIR}/glew/include DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin/ )

    add_custom_command( OUTPUT ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glew_s> ${CMAKE_CURRENT_LIST_DIR}/bin/
        COMMAND touch ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        DEPENDS glew_s
    )
    add_custom_target( glew_copy_files ALL
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
    )

    get_target_property( GLEW_INTERFACE_INCLUDE glew_s INTERFACE_INCLUDE_DIRECTORIES )

    list( APPEND GLEW_INTERFACE_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/glew/include )

    set_target_properties( glew_s
        PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INTERFACE_INCLUDE}"
    )

endif()
