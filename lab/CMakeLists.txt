file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.cpp
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp>)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE  ${SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    GLFW_INCLUDE_NONE=1
    $<$<CONFIG:Debug>:LAB_DEBUG=1>
    $<$<CONFIG:RelWithDebInfo>:LAB_DEVELOPMENT=1>
    $<$<CONFIG:Release>:LAB_SHIP=1>
    $<$<PLATFORM_ID:Linux>:LAB_LINUX=1>
    $<$<PLATFORM_ID:Windows>:LAB_WINDOWS=1>)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/
    #${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/)

include(SetVendorOutput)
set_vendor_output("glad")
set_vendor_output("glfw")
set_vendor_output("assimp")

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    glfw
    assimp
    glad
    #gtest
    OpenGL::GL)

include(CopyVendorOutput)
copy_vendor_output("assimp;assimp-vc143-mt.dll")
copy_vendor_output("glfw;glfw3.dll")
copy_vendor_output("glad;glad.lib")