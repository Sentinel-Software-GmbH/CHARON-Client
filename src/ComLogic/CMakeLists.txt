cmake_minimum_required(VERSION 3.19)
#set up module name for ComLogic
set(MODULE_NAME ComLogic)
#set up module name from businesslogic
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/SessionAndTransportManager.c
)
target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC 
  ${PROJECT_SOURCE_DIR}/include/ComLogic
  ${PROJECT_SOURCE_DIR}/include/Interfaces
  ${PROJECT_SOURCE_DIR}/include/DataModels
  ${PROJECT_SOURCE_DIR}/include/Common
)
