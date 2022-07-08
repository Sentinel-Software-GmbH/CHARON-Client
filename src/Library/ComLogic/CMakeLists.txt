cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME ComLogic)

add_library(${MODULE_NAME} SessionAndTransportManager.c)

target_include_directories(${MODULE_NAME}
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/Interfaces
  ${CMAKE_SOURCE_DIR}/include/DataModels
  
)
