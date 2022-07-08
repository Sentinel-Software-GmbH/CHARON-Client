cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME UploadDownload)

add_library(${MODULE_NAME} UploadDownload.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/Interfaces
  ${CMAKE_SOURCE_DIR}/include/DataModels  
)

target_link_libraries(${MODULE_NAME}
  PUBLIC
  ComLogic
  )