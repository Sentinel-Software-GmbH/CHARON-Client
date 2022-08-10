cmake_minimum_required(VERSION 3.19)
#set up project name and which languages are allowed to use
project(Charon_Client LANGUAGES C CXX)
#set up name for project top level
set(CHARON_SOURCE_DIR ${PROJECT_SOURCE_DIR})
#set up path where toolchain files and so on can be found for cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/toolchain/cmake)


add_subdirectory(src)
add_subdirectory(Ports)