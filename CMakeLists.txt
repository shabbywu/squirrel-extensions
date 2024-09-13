# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置 并包含子项目。
#
cmake_minimum_required(VERSION 3.12)
if(NOT WIN32)
  list(APPEND VCPKG_MANIFEST_FEATURES "with-opengl-tools-dependencies")
endif()

set(VCPKG_OVERLAY_PORTS )
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_LIST_DIR}/.vcpkg/triplets")
# Enable VCPKG if VCPKG_ROOT defined.
set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE
      "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project("bb-launcher")

# 设置 x86 架构
if(WIN32)
  set(CMAKE_GENERATOR_PLATFORM x86)
endif()
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/externals/sqbind17)
