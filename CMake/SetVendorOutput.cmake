function(set_vendor_output target)

    set(output_directory "${RENDER_LAB_ROOT_DIR}/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/$<CONFIG>")

    foreach(BUILD_TYPE Debug Release RelWithDebInfo MinSizeRel)

        set_target_properties(${target} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${output_directory}"
            LIBRARY_OUTPUT_DIRECTORY "${output_directory}"
            RUNTIME_OUTPUT_DIRECTORY "${output_directory}")

    endforeach()

endfunction()