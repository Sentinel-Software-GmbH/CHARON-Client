#set name for windows client port
set(MODULE_NAME charonClientWindows)
#create executable for client port also  link all  needed librariers 
add_executable(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/main/main.c
    $<TARGET_OBJECTS:PortWindows_wincom>
    $<TARGET_OBJECTS:PortWindows_Timer>
    $<TARGET_OBJECTS:PortWindows_communicationTest>
  )
target_link_libraries(${MODULE_NAME} 
  PUBLIC
    charon_DataTransmitter-Interface
    charon_DTC-Interface
    charon_DTC
    charon_UDSClientLib-Interface
    charon_UDSClientLib
    charon_DCM-Interface
    charon_DCM
    charon_compiler-Interface
    ${CHARON_CONFIG}
    PortWindows_communicationTest-Interface
    charon_DataModels
    charon_ErrorCode
  )

add_subdirectory(src)



    
    
    
   
   
    