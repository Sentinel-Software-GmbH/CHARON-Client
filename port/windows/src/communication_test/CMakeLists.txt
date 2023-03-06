set(MODULE_NAME PortWindows_communicationTest)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/port/windows/inc/communication_test
  )

add_library(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/communication_test.c
  )
target_link_libraries(${MODULE_NAME}
  PUBLIC  
    ${MODULE_NAME}-Interface
  PRRAVTE
    charon_DTC-Interface
    charon_DCM-Interface
    charon_UDSClientLib-Interface
    charon_compiler-Interface
    charon_DataModels
    ${CHARON_CONFIG}
  )