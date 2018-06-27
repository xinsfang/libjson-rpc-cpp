#define CATCH_CONFIG_MAIN
#include <curl/curl.h>
#include <catch.hpp>

#include "TestClientConnectionHandler.h"
#include "httpserver.h"

using namespace jsonrpc;
using namespace std;

#define TEST_MODULE "[connector-microhttpd]"

#define TEST_PORT 8383
#define CLIENT_URL "http://localhost:8383"

struct F {
  HttpServer server;
  TestClienctConnectionHandler handler;
  F() : server(TEST_PORT) {
    server.AddConnectionHandler(handler);
    REQUIRE(server.StartListening() == true);
  }

  ~F() { server.StopListening(); }
};

TEST_CASE_METHOD(F, "server_start_stop", TEST_MODULE) {
  REQUIRE(server.StartListening() == false);
  REQUIRE(server.StopListening() == true);
  REQUIRE(server.StopListening() == false);
}

TEST_CASE_METHOD(F, "http_get", TEST_MODULE) {
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
  CURLcode code = curl_easy_perform(curl);
  REQUIRE(code == CURLE_OK);

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  REQUIRE(http_code == 405);

  curl_easy_cleanup(curl);
}

TEST_CASE_METHOD(F, "http_options", TEST_MODULE) {
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
  CURLcode code = curl_easy_perform(curl);
  REQUIRE(code == CURLE_OK);

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  CHECK(http_code == 200);

  curl_easy_cleanup(curl);
}

TEST_CASE_METHOD(F, "http_post", TEST_MODULE)
{
  handler.response = "This is a microhttpd response";
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "This is a curl request");
   
  CURLcode result = curl_easy_perform(curl);

  REQUIRE(result == CURLE_OK);

  REQUIRE(handler.request == "This is a curl request");

  curl_easy_cleanup(curl);
}