
add_library(jsonrpccpp-client 
    batchcall.h
    batchcall.cpp
    batchresponse.h
    batchresponse.cpp
    client.h
    client.cpp
)

if(COMPILE_TESTS)
  target_sources(jsonrpccpp-unittest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/client_test.cpp)
  add_test(connector-client ${CMAKE_BINARY_DIR}/jsonrpccpp-unittest --durations yes "[client]")
endif()