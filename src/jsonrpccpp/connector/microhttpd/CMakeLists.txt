set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(MHD REQUIRED)
include_directories(${MHD_INCLUDE_DIR})

add_library(jsonrpccpp-connector-microhttpd httpserver.h httpserver.cpp)
target_link_libraries(jsonrpccpp-connector-microhttpd ${MHD_LIBRARIES})

if(COMPILE_TESTS)
  find_package(CURL REQUIRED)
  #find_package(Catch2 CONFIG REQUIRED)
  include_directories(${CURL_INCLUDE_DIR})

  add_executable(jsonrpccpp-connector-microhttpd-test httpserver_test.cpp)
  target_link_libraries(jsonrpccpp-connector-microhttpd-test PRIVATE jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
  add_test(connector-microhttpd jsonrpccpp-connector-microhttpd-test --durations yes)
endif()