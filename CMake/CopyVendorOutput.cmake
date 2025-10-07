function (copy_vendor_output data_list)

    list(GET data_list 0 target)
    list(GET data_list 1 target_output)

    set(target_path "${RENDER_LAB_ROOT_DIR}/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/$<CONFIG>/${target_output}")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${target_path}"
        "${RENDER_LAB_OUTPUT_DIR}/")

endfunction()