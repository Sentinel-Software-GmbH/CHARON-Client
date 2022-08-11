cmake_minimum_required(VERSION 3.19)
#set name for windows client port
set(MODULE_NAME charonClientWindows)
#create executable for client port also  link all  needed librariers 
add_executable(${MODULE_NAME}
  ${CMAKE_CURRENT_LIST_DIR}/src/main.c
  ${CMAKE_CURRENT_LIST_DIR}/src/timer.c
  ${CMAKE_CURRENT_LIST_DIR}/src/wincom.c
)
target_link_libraries(${MODULE_NAME} 
  PUBLIC
  DataTransmitter
  DTC
  UDSClientLib
  DCM
)