set(MODULE_NAME charon_ErrorCode)

add_library(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/ErrorCode.c
  )
target_link_libraries(${MODULE_NAME}
  PRIVATE
    charon_DataModels    
  )