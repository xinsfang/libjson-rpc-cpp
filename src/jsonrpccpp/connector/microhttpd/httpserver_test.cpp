#define CATCH_CONFIG_MAIN
#include <curl/curl.h>
#include <catch.hpp>

#include "httpserver.h"
#include "mockclientconnectionhandler.h"
using namespace jsonrpc;
using namespace std;

#define TEST_MODULE "[connector-microhttpd]"

#define TEST_PORT 8383
#define CLIENT_URL "http://localhost:8383"

namespace testhttpserver {
struct F {
  HttpServer server;
  MockClientConnectionHandler handler;

  F() : server(TEST_PORT) {
    server.AddConnectionHandler(handler);
    server.StartListening();
  }
  ~F() { server.StopListening(); }
};

} 
using namespace testhttpserver;

TEST_CASE_METHOD(F, "test_http_get", TEST_MODULE) {
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
  CURLcode code = curl_easy_perform(curl);
  REQUIRE(code == CURLE_OK);

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  CHECK(http_code == 405);

  curl_easy_cleanup(curl);
}

TEST_CASE_METHOD(F, "test_http_get_options", TEST_MODULE) {
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
  CURLcode code = curl_easy_perform(curl);
  REQUIRE(code == CURLE_OK);

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  CHECK(http_code == 200); // No error when server asked for OPTIONS.

  curl_easy_cleanup(curl);
}

/*
TEST_CASE("test_http_client_error", TEST_MODULE) {
  HttpClient client("http://someinvalidurl/asdf");
  string result;
  CHECK_EXCEPTION_TYPE(client.SendRPCMessage("asdfasfwer", result),
                       JsonRpcException, check_exception1);
}

#ifndef WIN32
TEST_CASE("test_http_server_multiplestart", TEST_MODULE) {
  HttpServer server(TEST_PORT);
  CHECK(server.StartListening() == true);

  HttpServer server2(TEST_PORT);
  CHECK(server2.StartListening() == false);

  CHECK(server.StopListening() == true);
}
#endif

TEST_CASE_METHOD(F, "test_http_client_timeout", TEST_MODULE) {
  handler.timeout = 20;
  client.SetTimeout(10);
  string result;
  CHECK_EXCEPTION_TYPE(client.SendRPCMessage("Test", result), JsonRpcException,
                       check_exception1);
  handler.timeout = 0;
  client.SetTimeout(10000);
  handler.response = "asdf";
  client.SendRPCMessage("", result);
  CHECK(result == "asdf");
  server.StopListening();
  CHECK_EXCEPTION_TYPE(client.SendRPCMessage("Test", result), JsonRpcException,
                       check_exception1);
}

TEST_CASE("test_http_client_headers", TEST_MODULE) {
  TestHttpServer server(TEST_PORT);
  HttpClient client(CLIENT_URL);

  REQUIRE(server.StartListening() == true);
  client.AddHeader("X-Auth", "1234");
  server.SetResponse("asdf");
  string result;
  client.SendRPCMessage("", result);
  CHECK(result == "asdf");
  CHECK(server.GetHeader("X-Auth") == "1234");

  client.RemoveHeader("X-Auth");
  client.SendRPCMessage("", result);
  CHECK(server.GetHeader("X-Auth") == "");

  server.StopListening();
}



TEST_CASE("test_http_server_endpoints", TEST_MODULE) {
  MockClientConnectionHandler handler1;
  MockClientConnectionHandler handler2;

  handler1.response = "response1";
  handler2.response = "response2";

  HttpServer server(TEST_PORT);
  server.SetUrlHandler("/handler1", &handler1);
  server.SetUrlHandler("/handler2", &handler2);

  REQUIRE(server.StartListening() == true);
  HttpClient client1("http://localhost:8383/handler1");
  HttpClient client2("http://localhost:8383/handler2");
  HttpClient client3("http://localhost:8383/handler3");

  string response;
  client1.SendRPCMessage("test", response);
  CHECK(response == "response1");
  client2.SendRPCMessage("test", response);
  CHECK(response == "response2");

  CHECK_EXCEPTION_TYPE(client3.SendRPCMessage("test", response),
                       JsonRpcException, check_exception2);

  client3.SetUrl("http://localhost:8383/handler2");
  client3.SendRPCMessage("test", response);
  CHECK(response == "response2");

  server.StopListening();
}

TEST_CASE_METHOD(F, "test_http_server_longpost", TEST_MODULE) {
  int mb = 5;
  unsigned long size = mb * 1024 * 1024;
  char *str = (char *)malloc(size * sizeof(char));
  if (str == NULL) {
    FAIL("Could not allocate enough memory for test");
  }
  for (unsigned long i = 0; i < size; i++) {
    str[i] = (char)('a' + (i % 26));
  }
  str[size - 1] = '\0';

  handler.response = str;
  string response;
  client.SetTimeout(-1);
  client.SendRPCMessage(str, response);

  CHECK(handler.request == str);
  CHECK(response == handler.response);
  CHECK(response.size() == size - 1);

  free(str);
}

TEST_CASE("test_http_server_ssl", TEST_MODULE) {
  HttpServer server(TEST_PORT, "/a/b/c", "/d/e/f");
  CHECK(server.StartListening() == false);

  HttpServer server2(TEST_PORT, "server.pem", "server.key");
  CHECK(server2.StartListening() == true);
  server2.StopListening();
}
*/