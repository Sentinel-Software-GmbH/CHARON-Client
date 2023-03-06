set(MODULE_NAME charon_Interfaces)

add_library(${MODULE_NAME}
  INTERFACE
  )
target_include_directories(${MODULE_NAME}
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/Interfaces
  )
