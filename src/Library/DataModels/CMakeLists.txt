cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DataModels)

add_library(${MODULE_NAME} 
  ErrorCode.c 
  MemoryDefinition.c
  )

target_include_directories(${MODULE_NAME} 
  PUBLIC
  ${CHARON_SOURCE_DIR}/include
  ${CHARON_SOURCE_DIR}/include/DataModels

)
  