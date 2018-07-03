set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(MHD REQUIRED)
include_directories(${MHD_INCLUDE_DIR})

add_library(jsonrpccpp-connector-microhttpd microhttpserver.h microhttpserver.cpp)
target_link_libraries(jsonrpccpp-connector-microhttpd ${MHD_LIBRARIES})

if(COMPILE_TESTS)
  find_package(CURL REQUIRED)

  file(COPY ${CMAKE_SOURCE_DIR}/src/examples/server.key ${CMAKE_SOURCE_DIR}/src/examples/server.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  add_executable(jsonrpccpp-connector-microhttpd-test microhttpserver_test.cpp)
  target_link_libraries(jsonrpccpp-connector-microhttpd-test PRIVATE jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
  add_test(connector-microhttpd jsonrpccpp-connector-microhttpd-test --durations yes)
endif()