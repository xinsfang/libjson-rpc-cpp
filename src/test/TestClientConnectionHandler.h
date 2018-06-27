#pragma once

#include <jsonrpccpp/connector/iclientconnectionhandler.h>
#include <chrono>
#include <thread>

class TestClienctConnectionHandler : public jsonrpc::IClientConnectionHandler {
 public:
  TestClienctConnectionHandler() : response(""), request(""), timeout(0) {}

  virtual std::string HandleRequest(const std::string& request) {
    std::this_thread::sleep_for(std::chrono::microseconds(timeout * 1000));
    this->request = request;
    return response;
  }

  std::string response;
  std::string request;
  long timeout;
};