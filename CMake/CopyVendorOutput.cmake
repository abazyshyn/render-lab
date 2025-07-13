function (copy_vendor_output data_list)

message(data_list "${data_list}")

    list(GET data_list 0 target)
    list(GET data_list 1 target_output)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/lab/vendor/${target}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${target}/${CMAKE_BUILD_TYPE}/${target_output}"
        "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/"
        COMMENT "Copied ${target_output}"
    )

endfunction()