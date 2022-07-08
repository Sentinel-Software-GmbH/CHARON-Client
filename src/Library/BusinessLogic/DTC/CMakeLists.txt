cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DTC)

add_library(${MODULE_NAME} StoredDataTransmitter.c)

target_include_directories(${MODULE_NAME}
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_SOURCE_DIR}/include/Interfaces
  ${CMAKE_SOURCE_DIR}/include/DataModels
)

target_link_libraries(${MODULE_NAME}
  PUBLIC
  ComLogic
 )