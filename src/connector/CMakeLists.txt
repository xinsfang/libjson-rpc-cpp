if(COMPILE_TESTS)
  add_executable(jsonrpccpp-abstractserverconnector-test abstractserverconnector_test.cpp)
  add_test(connector-abstractserverconnector jsonrpccpp-abstractserverconnector-test --durations yes)
endif()