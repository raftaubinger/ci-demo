cmake_minimum_required(VERSION 3.30)

set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(ci-demo LANGUAGES C)

add_subdirectory(library)

if(BUILD_TYPE STREQUAL cxarm OR NOT BUILD_TYPE)
  add_subdirectory(arm)
else()
  add_subdirectory(rl78)
endif()

