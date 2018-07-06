install(FILES iclientconnectionhandler.h abstractserverconnector.h 
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jsonrpccpp/connector
)

if(COMPILE_TESTS)
  add_executable(jsonrpccpp-abstractserverconnector-test abstractserverconnector_test.cpp)
  add_test(connector-abstractserverconnector jsonrpccpp-abstractserverconnector-test --durations yes)
endif()

