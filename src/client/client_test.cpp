#include "client.h"
#include <catch/catch.hpp>
#include "../connector/test_clientconnector.h"

#define TEST_MODULE "[client]"

using namespace std;
using namespace jsonrpc;
using namespace nlohmann;

struct ClientTest {
  TestClientConnector connector;
  Client clientv1;
  Client clientv2;

  ClientTest()
      : clientv1(connector, clientVersion_t::JSONRPC_CLIENT_V1),
        clientv2(connector, clientVersion_t::JSONRPC_CLIENT_V2) {}
};

TEST_CASE_METHOD(ClientTest, "clientv2_rpc_call", TEST_MODULE) { 
    connector.response = "";
    clientv2.CallMethod("somemethod", {{"a", 3}, {"b", 4}}); 
}

TEST_CASE_METHOD(ClientTest, "clientv2_rpc_call2", TEST_MODULE) { 
    connector.response = "";
    clientv2.CallMethod("somemethod", {{"a", 3}, {"b", 4}}); 
}