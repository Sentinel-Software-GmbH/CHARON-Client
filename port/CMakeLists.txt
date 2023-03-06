#add port directory depending on preset
if(Low_Port STREQUAL windows )
  add_subdirectory(windows)
elseif(Low_Port STREQUAL stm32f4)
  add_subdirectory(stm32f4-discovery)
elseif(Low_Port STREQUAL demo)
  add_subdirectory(demo)
endif()