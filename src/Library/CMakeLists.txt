cmake_minimum_required(VERSION 3.19)

add_subdirectory(BusinessLogic)
add_subdirectory(ComLogic)
add_subdirectory(DataModels)

set(MODULE_NAME UDSClientLib)

add_library(${MODULE_NAME} UDSClientLib.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${CHARON_SOURCE_DIR}/include
)
target_link_libraries(${MODULE_NAME} 
  PRIVATE
  DataTransmitter
)