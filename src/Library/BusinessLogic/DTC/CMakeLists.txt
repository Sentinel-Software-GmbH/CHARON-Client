cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME DTC)

add_library(${MODULE_NAME} StoredDataTransmitter.c)

target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC 
  ${PROJECT_SOURCE_DIR}/include/BusinessLogic/DTC
  ${PROJECT_SOURCE_DIR}/include/DataModels
)
target_link_libraries(${MODULE_NAME}
  PUBLIC
  ComLogic
)