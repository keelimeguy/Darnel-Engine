cmake_minimum_required( VERSION 3.13.2 )

option( GLM_STATIC_LIBRARY_ENABLE "GLM static library" ON )
option( GLM_DYNAMIC_LIBRARY_ENABLE "GLM shared library" OFF )

if( NOT ${GLM_LIBRARY_RELEASE} MATCHES "GLM_LIBRARY_RELEASE-NOTFOUND" )
    add_library( glm_static INTERFACE )
    target_include_directories( glm_static
        INTERFACE ${CMAKE_CURRENT_LIST_DIR}/bin/include
    )

    get_filename_component( ITEM_PATH ${GLM_LIBRARY_RELEASE} DIRECTORY )
    get_filename_component( ITEM_NAME ${GLM_LIBRARY_RELEASE} NAME )

    target_link_libraries( glm_static
        INTERFACE ${GLM_LIBRARY_RELEASE}
    )

else()
    execute_process( COMMAND git submodule update --init glm
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    add_subdirectory( glm EXCLUDE_FROM_ALL )

    set_target_properties( glm_shared
        PROPERTIES
            FOLDER "GLM"
    )

    set_target_properties( glm_static
        PROPERTIES
            FOLDER "GLM"
    )

    get_target_property( GLM_INCLUDE glm_static INCLUDE_DIRECTORIES )
    set_target_properties( glm_static
        PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GLM_INCLUDE}"
    )

    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    file( MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/include )
    file( COPY ${CMAKE_CURRENT_LIST_DIR}/glm/glm DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin/include/ )

    add_custom_command( OUTPUT ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glm_static> ${CMAKE_CURRENT_LIST_DIR}/bin/
        COMMAND touch ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
        DEPENDS glm_static
    )
    add_custom_target( glm_copy_files ALL
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bin/.dummy
    )

endif()
