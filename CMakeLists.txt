# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置 并包含子项目。
#
cmake_minimum_required(VERSION 3.13)

set(VCPKG_OVERLAY_PORTS)
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/triplets")
# Enable VCPKG if VCPKG_ROOT defined.
set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE
      "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project("squirrel-extensions")
set(CMAKE_CXX_STANDARD 17)
set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/include)
set(EXTERNAL_LIBS_DIR ${CMAKE_CURRENT_LIST_DIR}/externals/libs)

# 设置 x86 架构
if(WIN32)
  set(CMAKE_GENERATOR_PLATFORM x86)
endif()
set(CMAKE_CXX_STANDARD 20)

set(BUILD_SQUIRREL ON)
set(SQUIRREL305 1)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/externals/sqbind17)

add_subdirectory(modules/json)
add_subdirectory(test/sq_repl)
