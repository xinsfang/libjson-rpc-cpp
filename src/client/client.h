#pragma once

#include <atomic>
#include <nlohmann/json.hpp>
#include "../connector/iclientconnector.h"
#include "batchcall.h"
#include "batchresponse.h"

namespace jsonrpc {
  class RpcProtocolClient;

  typedef enum { JSONRPC_CLIENT_V1, JSONRPC_CLIENT_V2 } clientVersion_t;

  class Client {
   public:
    Client(IClientConnector &connector, clientVersion_t version = JSONRPC_CLIENT_V2);

    nlohmann::json CallMethod(const std::string &name, const nlohmann::json &parameter);
    BatchResponse CallProcedures(const BatchCall &calls);
    void CallNotification(const std::string &name, const nlohmann::json &parameter);

   private:
    IClientConnector &connector;
    clientVersion_t version;
    std::atomic<unsigned long> nextId;
  };
}