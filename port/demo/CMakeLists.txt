cmake_minimum_required(VERSION 3.19)
#set name for windows client port
set(MODULE_NAME charonClientdemoShowCase)

#create executable for client port also  link all  needed librariers 
add_executable(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/main/main.c
    $<TARGET_OBJECTS:PortShowcaseDemo_demoFeatures>
    $<TARGET_OBJECTS:PortShowcaseDemo_Timer>
    $<TARGET_OBJECTS:PortShowcaseDemo_wincom>
  )
target_link_libraries(${MODULE_NAME} 
  PUBLIC
    PortShowcaseDemo_demoFeatures-Interface
    charon_DataTransmitter-Interface
    charon_DataTransmitter
    charon_DTC-Interface
    charon_DTC
    charon_UDSClientLib-Interface
    charon_UDSClientLib
    charon_DCM-Interface
    charon_DCM
    charon_compiler-Interface
    charon_DataModels
    charon_ErrorCode
    ${CHARON_CONFIG}
  )

add_subdirectory(src)