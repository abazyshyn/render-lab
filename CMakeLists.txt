cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)
project(RenderLab VERSION 1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(WIN32)
  set(WINDOWS TRUE)
endif()
if(APPLE)
  set(MACOS TRUE)
endif()
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

set(RENDER_LAB "${PROJECT_NAME}")
set(RENDER_LAB_ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(RENDER_LAB_OUTPUT_DIR
    "${RENDER_LAB_ROOT_DIR}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}/${RENDER_LAB}/$<CONFIG>")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/")

include(AddGitSubmodule)
#add_git_submodule(vendor/assimp)
add_git_submodule(vendor/glfw)
add_git_submodule(vendor/glm)
#add_git_submodule(vendor/googletest)

add_subdirectory(lab/vendor/glad)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${RENDER_LAB_ROOT_DIR}/src/*.cpp"
    "${RENDER_LAB_ROOT_DIR}/src/*.hpp"
    "${RENDER_LAB_ROOT_DIR}/vendor/stb_image/stb_image.cpp")

add_executable("${RENDER_LAB}")

target_sources("${RENDER_LAB}" PRIVATE  "${SOURCE_FILES}")

set_target_properties("${RENDER_LAB}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${RENDER_LAB_OUTPUT_DIR}/")

target_compile_definitions(${RENDER_LAB}
    PUBLIC $<$<BOOL:${WINDOWS}>:LAB_WINDOWS=1>
    $<$<BOOL:${LINUX}>:LAB_LINUX=1>
    PRIVATE GLFW_INCLUDE_NONE=1
    LAB_RES_DIR="${RENDER_LAB_ROOT_DIR}/res/"
    $<$<CONFIG:Debug>:LAB_DEBUG=1>
    $<$<CONFIG:RelWithDebInfo>:LAB_DEVELOPMENT=1>
    $<$<CONFIG:Release>:LAB_SHIP=1>)

target_include_directories(${RENDER_LAB} PUBLIC
    "${RENDER_LAB_ROOT_DIR}/src/"
    "${RENDER_LAB_ROOT_DIR}/vendor/assimp/include/"
    "${RENDER_LAB_ROOT_DIR}/vendor/glad/include/"
    "${RENDER_LAB_ROOT_DIR}/vendor/glfw/include/"
    "${RENDER_LAB_ROOT_DIR}/vendor/glm/"
    "${RENDER_LAB_ROOT_DIR}/vendor/stb_image/")

include(SetVendorOutput)
set_vendor_output("glad")
set_vendor_output("glfw")
#set_vendor_output("assimp")

target_precompile_headers("${RENDER_LAB}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp")

target_link_libraries("${RENDER_LAB}" PUBLIC
    glfw
    #assimp
    glad
    OpenGL::GL)

if(WINDOWS)
  include(CopyVendorOutput)
  copy_vendor_output("assimp;assimp-vc143-mtd.dll")
  copy_vendor_output("glfw;glfw3d.dll")
  copy_vendor_output("glad;gladd.lib")
endif()
