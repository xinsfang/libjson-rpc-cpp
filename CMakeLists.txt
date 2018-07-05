cmake_minimum_required(VERSION 3.0)

project(libjson-rpc-cpp)

set(MAJOR_VERSION 2)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(SO_VERSION    2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(COMPILE_TESTS "compile with testing support" ON)
option(CONNECTOR_MICROHTTPD "libmicrohttpd based server connector" ON)

include(GNUInstallDirs)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wformat -Wno-format-extra-args -Wformat-security -Wformat-nonliteral -Wformat=2 -Wextra -Wnon-virtual-dtor")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()


if(COMPILE_TESTS)
  enable_testing()
  include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
endif()

if(CONNECTOR_MICROHTTPD)
  add_subdirectory(src/connector/microhttpd)
endif()


