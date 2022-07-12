cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME charonClientWindows)

add_executable(${MODULE_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/src/timer.c
  ${CMAKE_CURRENT_LIST_DIR}/src/wincom.c
)

target_link_directories(${MODULE_NAME}
  PRIVATE
  ${CHARON_SOURCE_DIR}/include
  ${CHARON_SOURCE_DIR}/include/Interfaces
)

target_link_libraries(${MODULE_NAME} 
  PUBLIC
  DataTransmitter
  UDSClientLib
  DCM
)