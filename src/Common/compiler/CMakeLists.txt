set(MODULE_NAME charon_compiler)

add_library(${MODULE_NAME}-Interface
  INTERFACE
  )
target_include_directories(${MODULE_NAME}-Interface
  INTERFACE
    ${CHARON_SOURCE_DIR}/include/Common/compiler
  )