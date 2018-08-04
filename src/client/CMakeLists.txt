
add_library(jsonrpccpp-client 
    batchcall.h
    batchcall.cpp
    batchresponse.h
    batchresponse.cpp
    client.h
    client.cpp
)

if(COMPILE_TESTS)
  add_executable(jsonrpccpp-client-test client_test.cpp)
  target_link_libraries(jsonrpccpp-client-test PRIVATE jsonrpccpp-client)
  add_test(client ${CMAKE_BINARY_DIR}/jsonrpccpp-client-test --durations yes)
endif()