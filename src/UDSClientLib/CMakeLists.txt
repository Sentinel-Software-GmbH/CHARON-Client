#set up module name for UDS Client Library
set(MODULE_NAME charon_UDSClientLib)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/UDSClientLib
  )
target_link_libraries(${MODULE_NAME}-Interface
  INTERFACE  
    charon_SessionAndTransportManger-Interface
    charon_Interfaces
    charon_compiler-Interface
    charon_DataModels
    ${CHARON_CONFIG}
  )

#create library and link all needed librariers
add_library(${MODULE_NAME} 
  ${CMAKE_CURRENT_LIST_DIR}/UDSClientLib.c
)
target_link_libraries(${MODULE_NAME}
  PRIVATE
    ${MODULE_NAME}-Interface 
  )