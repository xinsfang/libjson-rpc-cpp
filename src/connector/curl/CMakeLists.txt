find_package(CURL REQUIRED)

add_library(jsonrpccpp-connector-curl curlclient.h curlclient.cpp)
target_link_libraries(jsonrpccpp-connector-curl ${CURL_LIBRARIES})

set_target_properties(jsonrpccpp-connector-curl PROPERTIES
  PUBLIC_HEADER "curlclient.h"
  SOVERSION ${SO_VERSION}
  VERSION ${VERSION_STRING}
)

install(TARGETS jsonrpccpp-connector-curl 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jsonrpccpp/connector/curl
)