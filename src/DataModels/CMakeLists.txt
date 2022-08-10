cmake_minimum_required(VERSION 3.19)
#set up module name for DataModels library
set(MODULE_NAME DataModels)
#set up module name from businesslogic
add_library(${MODULE_NAME} 
  ErrorCode.c 
  MemoryDefinition.c
)
target_include_directories(${MODULE_NAME} 
  INTERFACE PUBLIC
  ${CHARON_SOURCE_DIR}/include/DataModels
)
  