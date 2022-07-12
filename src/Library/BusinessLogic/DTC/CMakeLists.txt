cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DTC)

add_library(${MODULE_NAME} StoredDataTransmitter.c)

target_include_directories(${MODULE_NAME}
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}
  ${PROJECT_SOURCE_DIR}/include/Interfaces
  ${PROJECT_SOURCE_DIR}/include/DataModels
  ${PROJECT_SOURCE_DIR}/src/Library
)

target_link_libraries(${MODULE_NAME}
  PUBLIC
  ComLogic
 )