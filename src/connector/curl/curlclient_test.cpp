#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <iostream>
#include "../microhttpd/microhttpserver.h"
#include "../testclientconnectionhandler.h"
#include "../../exception.h"
#include "curlclient.h"

#define TEST_MODULE "[connector-curl]"

#define TEST_PORT 8484
#define CLIENT_URL "http://localhost:8484"

using namespace jsonrpc;
using namespace std;


struct F {
  TestClienctConnectionHandler handler;
  MicroHttpServer server;
  CurlClient client;

  F() : server(TEST_PORT, {handler}), client(CLIENT_URL, 1000, false) {
    handler.response = "mockresponse";
    REQUIRE(server.StartListening() == true);
  }
};


TEST_CASE_METHOD(F, "curl_post_success", TEST_MODULE) {
  string response = client.SendRPCMessage("this is a request");

  REQUIRE(response == handler.response);
  REQUIRE("this is a request" == handler.request);
}

TEST_CASE("curl_invalid_url", TEST_MODULE) {
  CurlClient client("http://someinvalidurl/asdf", 1000);
  try {
    client.SendRPCMessage("this is a request");
    FAIL("No invalid url exception has been thrown");
  } catch (JsonRpcException e) {
    REQUIRE(e.GetCode() == -32003);
    string message = e.what();
    REQUIRE(message == "JsonRpcException -32003: libcurl error 6, Couldn't resolve host name");
  }
}

TEST_CASE_METHOD(F, "curl_timeout", TEST_MODULE) {
  CurlClient client(CLIENT_URL, 10);
  handler.timeout = 12;
  try {
    client.SendRPCMessage("this is a request");
    FAIL("No timeout exception has been thrown");
  } catch (JsonRpcException e) {
    REQUIRE(e.GetCode() == -32003);
    string message = e.what();
    REQUIRE(message == "JsonRpcException -32003: libcurl error 28, Timeout was reached");
  }
}

TEST_CASE_METHOD(F, "curl_tls_invalid", TEST_MODULE) {
  if (!MHD_is_feature_supported(MHD_FEATURE_SSL)) {
    WARN("HTTPS won't be tested due to missing TLS support in libmicrohttpd");
  } else {
    CurlClient client("https://localhost:8484");
    server.StopListening();
    REQUIRE(server.EnableTLS("server.pem", "server.key") == true);
    REQUIRE(server.StartListening() == true);
    try {
      client.SendRPCMessage("request");
      FAIL("No tls exception has been thrown");
    } catch (JsonRpcException e) {
        REQUIRE(e.GetCode() == -32003);
        string message = e.what();
        REQUIRE(message == "JsonRpcException -32003: libcurl error 60, Peer certificate cannot be authenticated with given CA certificates");
    }
  }
}

TEST_CASE_METHOD(F, "curl_tls_valid", TEST_MODULE) {
  if (!MHD_is_feature_supported(MHD_FEATURE_SSL)) {
    WARN("HTTPS won't be tested due to missing TLS support in libmicrohttpd");
  } else {
    CurlClient client("https://localhost:8484", 0, false);
    server.StopListening();
    REQUIRE(server.EnableTLS("server.pem", "server.key") == true);
    REQUIRE(server.StartListening() == true);
    try {
      REQUIRE(client.SendRPCMessage("request") == "mockresponse");
      REQUIRE(handler.request == "request");
    } catch (JsonRpcException e) {
      FAIL("No tls exception expected");
    }
  }
}