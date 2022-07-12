cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DCM)

add_library(${MODULE_NAME} DiagnosticCommunicationManager.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/Interfaces
  ${PROJECT_SOURCE_DIR}/include/DataModels
)

target_link_libraries(${MODULE_NAME}
  PUBLIC
  ComLogic
  )