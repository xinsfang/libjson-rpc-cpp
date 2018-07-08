set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(MHD REQUIRED)
include_directories(${MHD_INCLUDE_DIR})

add_library(jsonrpccpp-connector-microhttpd microhttpserver.h microhttpserver.cpp)
target_link_libraries(jsonrpccpp-connector-microhttpd ${MHD_LIBRARIES})

set_target_properties(jsonrpccpp-connector-microhttpd PROPERTIES
  PUBLIC_HEADER "microhttpserver.h"
  SOVERSION ${SO_VERSION}
  VERSION ${VERSION_STRING}
)

configure_file(jsonrpccpp-connector-microhttpd.pc.in ${CMAKE_BINARY_DIR}/jsonrpccpp-connector-microhttpd.pc @ONLY)

install(TARGETS jsonrpccpp-connector-microhttpd 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jsonrpccpp/connector/microhttpd
)

install(FILES ${CMAKE_BINARY_DIR}/jsonrpccpp-connector-microhttpd.pc 
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

if(COMPILE_TESTS)
  find_package(CURL REQUIRED)

  file(COPY ${CMAKE_SOURCE_DIR}/src/examples/server.key ${CMAKE_SOURCE_DIR}/src/examples/server.pem DESTINATION ${CMAKE_BINARY_DIR})
  file(COPY ${CMAKE_SOURCE_DIR}/src/examples/server.key ${CMAKE_SOURCE_DIR}/src/examples/server.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  add_executable(jsonrpccpp-connector-microhttpd-test microhttpserver_test.cpp)
  target_link_libraries(jsonrpccpp-connector-microhttpd-test PRIVATE jsonrpccpp-connector-microhttpd ${CURL_LIBRARIES})
  add_test(connector-microhttpd ${CMAKE_BINARY_DIR}/jsonrpccpp-connector-microhttpd-test --durations yes)
endif()