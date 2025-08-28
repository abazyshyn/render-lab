file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.cpp)

add_executable(${RENDER_LAB})

target_sources(${RENDER_LAB} PRIVATE  ${SOURCE_FILES})

set_target_properties(${RENDER_LAB} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${RENDER_LAB_OUTPUT_DIR}/")

target_compile_definitions(${RENDER_LAB} 
    PUBLIC $<$<BOOL:${WINDOWS}>:LAB_WINDOWS=1>
    $<$<BOOL:${LINUX}>:LAB_LINUX=1>
    PRIVATE GLFW_INCLUDE_NONE=1
    $<$<CONFIG:Debug>:LAB_DEBUG=1>
    $<$<CONFIG:RelWithDebInfo>:LAB_DEVELOPMENT=1>
    $<$<CONFIG:Release>:LAB_SHIP=1>
    $<$<PLATFORM_ID:Linux>:LAB_LINUX=1>
    $<$<PLATFORM_ID:Windows>:LAB_WINDOWS=1>)

target_include_directories(${RENDER_LAB} PUBLIC 
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

target_precompile_headers(${RENDER_LAB} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp")

target_link_libraries(${RENDER_LAB} PUBLIC 
    glfw
    assimp
    glad
    #gtest
    OpenGL::GL)

if(WINDOWS)
    include(CopyVendorOutput)
    copy_vendor_output("assimp;*.dll")
    copy_vendor_output("glfw;*.dll")
    copy_vendor_output("glad;*.lib")
endif()
