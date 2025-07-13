function(set_vendor_output target)

    foreach(BUILD_TYPE Debug Release RelWithDebInfo MinSizeRel)

        set_target_properties(${target} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/${BUILD_TYPE}"
            LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/${BUILD_TYPE}"
            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/${BUILD_TYPE}"
        )

    endforeach()

endfunction()