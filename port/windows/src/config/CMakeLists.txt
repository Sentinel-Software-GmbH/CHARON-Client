set(MODULE_NAME ${CHARON_CONFIG})

add_library(${MODULE_NAME}
  INTERFACE
  )
target_include_directories(${MODULE_NAME}
  INTERFACE
    ${CHARON_SOURCE_DIR}/port/windows/inc/config
  )
