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