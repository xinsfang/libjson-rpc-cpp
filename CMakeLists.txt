cmake_minimum_required(VERSION 3.0)

project(libjson-rpc-cpp)

set(MAJOR_VERSION 2)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(SO_VERSION    2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(COMPILE_TESTS "compile with testing support" ON)
option(CONNECTOR_MICROHTTPD "libmicrohttpd based ServerConnector" ON)

include_directories("src")


if(COMPILE_TESTS)
  enable_testing()
  include_directories("src/test")
endif()


if(CONNECTOR_MICROHTTPD)
  add_subdirectory(src/jsonrpccpp/connector/microhttpd)
endif()


include(GNUInstallDirs)
