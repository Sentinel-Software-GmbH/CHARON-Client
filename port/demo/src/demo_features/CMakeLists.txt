set(MODULE_NAME PortShowcaseDemo_demoFeatures)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/port/demo/inc/demo_features
  )

add_library(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/demo.c
  )
target_link_libraries(${MODULE_NAME}
  PRIVATE
    ${MODULE_NAME}-Interface
    ${CHARON_CONFIG}
    charon_DataTransmitter-Interface
    charon_UDSClientLib-Interface
    charon_DCM-Interface
    charon_DTC-Interface
    charon_SessionAndTransportManger-Interface
    charon_SessionAndTransportManger  
    charon_DataModels 
    charon_compiler-Interface
  )