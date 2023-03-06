#set up module name from businesslogic
set(MODULE_NAME charon_Routine)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/BusinessLogic/Routine
  )

#create library and link all needed librariers
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/Routine.c
)
target_link_libraries(${MODULE_NAME} 
  PRIVATE
    ${MODULE_NAME}-Interface
    charon_SessionAndTransportManger-Interface
    charon_Interfaces
    charon_compiler-Interface
    charon_DataModels
    ${CHARON_CONFIG}
  )