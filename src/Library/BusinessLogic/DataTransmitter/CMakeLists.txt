cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DataTransmitter)

add_library(${MODULE_NAME} DataTransmitter.c)

target_include_directories(${MODULE_NAME}
  PUBLIC 
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/Interfaces
  ${PROJECT_SOURCE_DIR}/include/DataModels
  ${PROJECT_SOURCE_DIR}/src/Library
  )

target_link_libraries(${MODULE_NAME} 
  PRIVATE
  ComLogic
)