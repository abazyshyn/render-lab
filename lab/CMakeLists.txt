file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp>)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE  ${SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    GLFW_INCLUDE_NONE=1
    STB_IMAGE_IMPLEMENTATION=1
    $<$<CONFIG:Debug>:LAB_DEBUG=1>
    $<$<CONFIG:RelWithDebInfo>:LAB_DEVELOPMENT=1>
    $<$<CONFIG:Release>:LAB_SHIP=1>
    $<$<PLATFORM_ID:Linux>:LAB_LINUX=1>
    $<$<PLATFORM_ID:Windows>:LAB_WINDOWS=1>)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/
    #${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)

set_target_properties(glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glad/build"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glad/build"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glad/build"
)

set_target_properties(glfw PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glfw/build"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glfw/build"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/glfw/build"
)

set_target_properties(assimp PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/assimp/build"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/assimp/build"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lab/vendor/assimp/build"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    glfw
    assimp
    glad
    #gtest
    OpenGL::GL)
