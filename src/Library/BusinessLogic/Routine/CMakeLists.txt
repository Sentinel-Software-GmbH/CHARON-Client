cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME Routine)

add_library(${MODULE_NAME} Routine.c)

target_include_directories(${MODULE_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include/BusinessLogic/Routine
  ${PROJECT_SOURCE_DIR}/include/DataModels
)
target_link_libraries(${MODULE_NAME} 
  PRIVATE
  ComLogic
)