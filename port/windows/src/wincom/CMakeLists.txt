set(MODULE_NAME PortWindows_wincom)

add_library(${MODULE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/wincom.c
  )
target_link_libraries(${MODULE_NAME}
  PRIVATE
    charon_Interfaces
    )