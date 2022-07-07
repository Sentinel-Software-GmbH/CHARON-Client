cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DataTransmitter)

add_library(${MODULE_NAME} DataTransmitter.c)

target_include_directories(${MODULE_NAME}
  PRIVATE
  CMAKE_CURRENT_LIST_DIR/DataModels
  CMAKE_CURRENT_LIST_DIR/ComLogic
  CMAKE_SOURCE_DIR/include 
  )