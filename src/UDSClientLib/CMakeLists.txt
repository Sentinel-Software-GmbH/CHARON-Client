cmake_minimum_required(VERSION 3.19)
#set up module name for UDS Client Library
set(MODULE_NAME UDSClientLib)
#create library and link all needed librariers
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/UDSClientLib.c
)
target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC
  ${CHARON_SOURCE_DIR}/include/Common
  ${PROJECT_SOURCE_DIR}/include/Interface
  ${PROJECT_SOURCE_DIR}/include/DataModels
)
target_link_libraries(${MODULE_NAME}
  PRIVATE
  ComLogic
)