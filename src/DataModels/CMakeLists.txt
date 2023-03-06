add_subdirectory(Errorcode)
add_subdirectory(MemoryDefinition)


set(MODULE_NAME charon_DataModels)

add_library(${MODULE_NAME}
  INTERFACE
  )
target_include_directories(${MODULE_NAME}
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/DataModels
  )