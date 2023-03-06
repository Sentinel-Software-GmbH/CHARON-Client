#set up module name for ComLogic
set(MODULE_NAME charon_SessionAndTransportManger)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/ComLogic/SessionAndTransportManager
  )  
#set up module name from businesslogic
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/SessionAndTransportManager.c
)
target_link_libraries(${MODULE_NAME}
  PRIVATE
    ${MODULE_NAME}-Interface
    charon_DataModels
    charon_Interfaces
    ${CHARON_CONFIG}
  )