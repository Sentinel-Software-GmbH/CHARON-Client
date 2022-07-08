cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME Routine)

add_library(${MODULE_NAME} Routine.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/DataModels
  ${CMAKE_SOURCE_DIR}/include/Interfaces
)
