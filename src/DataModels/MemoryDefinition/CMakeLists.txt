set(MODULE_NAME charon_MemoryDefinition)

add_library(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/MemoryDefinition.c
  )
target_link_libraries(${MODULE_NAME}
  PRIVATE
    charon_DataModels    
  )