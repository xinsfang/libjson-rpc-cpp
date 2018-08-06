if (COVERAGE)
  include(CodeCoverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
  set(COVERAGE_EXCLUDES '/usr/*' '*/v1/*' '*/catch.hpp' '*/test_*' '*_test.cpp')
  SETUP_TARGET_FOR_COVERAGE(
     NAME coverage
     EXECUTABLE ctest .
     DEPENDENCIES build
  )
endif()

enable_testing()
add_executable(jsonrpccpp-unittest main.cpp)

if(JSONRPC_CLIENT)
  target_link_libraries(jsonrpccpp-unittest jsonrpccpp-client)
endif()

if(CONNECTOR_MICROHTTPD)
  find_package(CURL REQUIRED)
  target_link_libraries(jsonrpccpp-unittest jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
endif()

if(CONNECTOR_CURL)
  find_package(CURL REQUIRED)
  target_link_libraries(jsonrpccpp-unittest jsonrpccpp-connector-curl jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
endif()