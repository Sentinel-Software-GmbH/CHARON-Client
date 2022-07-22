cmake_minimum_required(VERSION 3.19)

project(Charon_Client LANGUAGES C CXX)

set(CHARON_SOURCE_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/toolchain/cmake)


add_subdirectory(src)
add_subdirectory(Ports)