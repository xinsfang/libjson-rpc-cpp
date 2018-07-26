#pragma once

#include <map>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "../exception.h"

namespace jsonrpc {

  class BatchResponse {
   public:
    BatchResponse(const nlohmann::json& response);

    nlohmann::json getResult(long id);

    JsonRpcException getError(long id);


    bool containsErrors();

   private:
    const nlohmann::json& response;
    bool errors;
    std::map<long, long> responseIndex;
    std::map<long, long> errorIndex;
    std::vector<long> unidentifiedErrors;
    
  };
}
