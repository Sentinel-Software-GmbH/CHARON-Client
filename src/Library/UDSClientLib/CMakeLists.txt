cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME UDSClientLib)

add_library(${MODULE_NAME} UDSClientLib.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${CHARON_SOURCE_DIR}/include/Common
)