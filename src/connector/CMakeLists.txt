if(COMPILE_TESTS)
  add_executable(jsonrpccpp-abstractserverconnector-test abstractserverconnector_test.cpp)
  add_test(jsonrpccpp-abstractserverconnector-test --durations yes)
endif()