cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME UDSClientLib)

add_library(${MODULE_NAME} UDSClientLib.c)

target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC
  ${CHARON_SOURCE_DIR}/include/Common
  ${PROJECT_SOURCE_DIR}/include/Interface
  ${PROJECT_SOURCE_DIR}/include/DataModels
)
target_link_libraries(${MODULE_NAME}
  PRIVATE
  ComLogic

)