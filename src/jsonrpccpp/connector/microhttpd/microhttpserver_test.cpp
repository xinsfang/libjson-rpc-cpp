#define CATCH_CONFIG_MAIN
#include <curl/curl.h>
#include <catch.hpp>

#include <string>

#include "TestClientConnectionHandler.h"
#include "microhttpserver.h"

using namespace jsonrpc;
using namespace std;

#define TEST_MODULE "[connector-microhttpd]"

#define TEST_PORT 8383
#define CLIENT_URL "http://localhost:8383"

struct F {
  MicroHttpServer server;
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

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

string ExecutePostRequest(const string &url, const string &content) {
  string response;
  CURL *curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, CLIENT_URL);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

  CURLcode result = curl_easy_perform(curl);

  REQUIRE(result == CURLE_OK);
  curl_easy_cleanup(curl);

  return response;
}

TEST_CASE_METHOD(F, "http_post", TEST_MODULE) {
  handler.response = "This is a microhttpd response";
  string response = ExecutePostRequest(CLIENT_URL, "This is a curl request");

  REQUIRE(handler.request == "This is a curl request");
  REQUIRE(response == handler.response);
}

TEST_CASE("https_invalid_paths", TEST_MODULE) {
  MicroHttpServer server(TEST_PORT);
  REQUIRE(server.EnableTLS("/a/b/c", "/d/e/f") == false);
  REQUIRE(server.StartListening() == true);
  REQUIRE(server.EnableTLS("server.pem", "server.key") == false);
  server.StopListening();
}

TEST_CASE("https_valid_startup", TEST_MODULE) {
  if (!MHD_is_feature_supported(MHD_FEATURE_SSL)) {
    WARN("HTTPS won't be tested due to missing TLS support in libmicrohttpd");
  } else {
    MicroHttpServer server(TEST_PORT);
    server.EnableTLS("server.pem", "server.key");

    TestClienctConnectionHandler handler;
    server.AddConnectionHandler(handler);

    REQUIRE(server.StartListening() == true);

    handler.response = "This is a microhttpd response";
    REQUIRE(ExecutePostRequest(CLIENT_URL, "This is a curl request") == handler.response);
    REQUIRE(handler.request == "This is a curl request");
    server.StopListening();
  }
}