cmake_minimum_required(VERSION 3.19)

add_subdirectory(BusinessLogic)
add_subdirectory(ComLogic)
add_subdirectory(DataModels)

set(MODULE_NAME UDSClientLib)

add_library(${MODULE_NAME} UDSClientLib.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  CMAKE_SOURCE_DIR/include
  PRIVATE
  CMAKE_CURRENT_SOURCE_DIR/ComLogic
)