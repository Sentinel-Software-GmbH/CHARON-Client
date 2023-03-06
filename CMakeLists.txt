cmake_minimum_required(VERSION 3.19)
#set up project name and which languages are allowed to use
project(Charon_Client LANGUAGES C CXX)
#set up name for project top level
set(CHARON_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
#set up path where toolchain files and so on can be found for cmake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/toolchain/cmake)

#set up name for charon config file to  specify which portis used
string(TOLOWER ${PORT} Low_Port)
if(Low_Port STREQUAL windows)
  set(CHARON_CONFIG "windowsConfig")
elseif(Low_Port STREQUAL stm32f4)
  set(CHARON_CONFIG "F4Config")
elseif(Low_Port STREQUAL standalone)
  set(CHARON_CONFIG "standAloneConfig")
elseif(Low_Port STREQUAL demo)
  set(CHARON_CONFIG "demoConfig")
endif()

add_subdirectory(src)
add_subdirectory(port)