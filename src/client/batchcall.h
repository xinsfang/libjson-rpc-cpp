#pragma once

#include <nlohmann/json.hpp>

namespace jsonrpc {
  class BatchCall {
   public:
    BatchCall();

    long addMethod(const std::string& methodname, nlohmann::json &params);
    void addNotification(const std::string&methodname, nlohmann::json &params);

    const nlohmann::json& getCall() const;
   private:
    nlohmann::json result;
    long nextId;
  };
}