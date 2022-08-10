cmake_minimum_required(VERSION 3.19)
#set up module name from businesslogic
set(MODULE_NAME Routine)
#create library and link all needed librariers
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/Routine.c
)
target_include_directories(${MODULE_NAME}
  INTERFACE PUBLIC
  ${PROJECT_SOURCE_DIR}/include/BusinessLogic/Routine
  ${PROJECT_SOURCE_DIR}/include/DataModels
  ${PROJECT_SOURCE_DIR}/include/Common
)
target_link_libraries(${MODULE_NAME} 
  PRIVATE
  ComLogic
)