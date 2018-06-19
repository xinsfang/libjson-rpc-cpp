cmake_minimum_required(VERSION 3.0)

project(libjson-rpc-cpp)

set(MAJOR_VERSION 2)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(SO_VERSION    2)

option(CONNECTOR_MICROHTTPD "libmicrohttpd based ServerConnector" ON)

include_directories("src")

if(CONNECTOR_MICROHTTPD)
  add_subdirectory(src/jsonrpccpp/connector/microhttpd)
endif()


include(GNUInstallDirs)
