cmake_minimum_required(VERSION 3.16)
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
set(RENDER_LAB_SRC_DIR "${RENDER_LAB_ROOT_DIR}/lab")
set(RENDER_LAB_OUTPUT_DIR
    "${RENDER_LAB_ROOT_DIR}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_HOST_SYSTEM_PROCESSOR}/${RENDER_LAB}/$<CONFIG>")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/")

include(AddGitSubmodule)
add_git_submodule(lab/vendor/assimp)
add_git_submodule(lab/vendor/glfw)
add_git_submodule(lab/vendor/glm)
#add_git_submodule(lab/vendor/googletest)

add_subdirectory(lab/vendor/glad)
add_subdirectory(lab)
