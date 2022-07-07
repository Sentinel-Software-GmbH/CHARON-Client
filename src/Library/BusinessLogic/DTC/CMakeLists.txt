cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DTC)

add_library(${MODULE_NAME} StoredDataTransmitter.c)

target_include_directories(${MODULE_NAME}
  PRIVATE
  CMAKE_SOURCE_DIR/src/ComLogic
  )