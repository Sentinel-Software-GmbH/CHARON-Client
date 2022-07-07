cmake_minimum_required(VERSION 3.19)

set(MODULE_NAME UploadDownload)

add_library(${MODULE_NAME} UploadDownload.c)

target_include_directories(${MODULE_NAME}
  PRIVATE
  CMAKE_SOURCE_DIR/include
  
)