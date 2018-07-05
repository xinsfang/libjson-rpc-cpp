#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <string>

#include "abstractserverconnector.h"
#include "testclientconnectionhandler.h"

using namespace jsonrpc;
using namespace std;

#define TEST_MODULE "[abstractserverconnector]"

class TestServerConnector : public AbstractServerConnector {
  virtual bool StartListening() { return true; }
  virtual bool StopListening() { return false; }
};

struct F {
  TestServerConnector server;
  TestClienctConnectionHandler handler;
  F() {
    server.AddConnectionHandler(handler);
    handler.response = "testresponse";
  }
};


TEST_CASE_METHOD(F, "test_valid_connectionhandler", TEST_MODULE) {
    string response = server.ProcessRequest("request1");
    REQUIRE(handler.request == "request1");
    REQUIRE(response == "testresponse");
}