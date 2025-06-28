cmake_minimum_required(VERSION 3.16)
project(RenderLab VERSION 1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(outputDir "${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${outputDir}/")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/")
include(AddGitSubmodule)

add_git_submodule(lab/vendor/assimp)
add_git_submodule(lab/vendor/glfw)
add_git_submodule(lab/vendor/glm)
#add_git_submodule(lab/vendor/googletest)

add_subdirectory(lab/vendor/glad)
add_subdirectory(lab)
