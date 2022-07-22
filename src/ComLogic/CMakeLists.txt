cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME ComLogic)

add_library(${MODULE_NAME} SessionAndTransportManager.c)

target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC 
  ${PROJECT_SOURCE_DIR}/include/ComLogic
  ${PROJECT_SOURCE_DIR}/include/Interfaces
  ${PROJECT_SOURCE_DIR}/include/DataModels
  ${PROJECT_SOURCE_DIR}/include/Common
)
