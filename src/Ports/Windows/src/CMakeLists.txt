cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME Charon_WindowsPort.exe)


add_executable(${MODULE_NAME}
  main.c
  timer.c
  wincom.c
)

target_link_directories(${MODULE_NAME}
  PUBLIC
  CMAKE_SOURCE_DIR/include
)

target_link_libraries(${MODULE_NAME} 
  PUBLIC
  UDSClientLib
)