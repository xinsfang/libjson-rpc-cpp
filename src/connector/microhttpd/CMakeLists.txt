find_library(MHD REQUIRED)

add_library(jsonrpccpp-connector-microhttpd httpserver.h httpserver.cpp)
target_link_libraries(jsonrpccpp-connector-microhttpd ${MHD_LIBRARIES})

if(COMPILE_TESTS)

  find_package(CURL REQUIRED)

  add_executable(jsonrpccpp-connector-microhttpd-test httpserver_test.cpp)
  target_link_libraries(jsonrpccpp-connector-microhttpd-test jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
endif()