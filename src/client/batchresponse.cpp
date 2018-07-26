#include "batchresponse.h"
#include <algorithm>
#include "../constants.h"

using namespace jsonrpc;
using namespace std;
using json = nlohmann::json;

BatchResponse::BatchResponse(const json& response) : response(response), errors(false) {
  int i = 0;
  for (auto& result : response) {
    if (result.find("id") != result.end()) {
      if (result.find(JSONRPCCPP_RESULT) != result.end())
        responseIndex[result[JSONRPCCPP_ID]] = i;
      else {
        errorIndex[result[JSONRPCCPP_ID]] = i;
        errors = true;
      }
    } else {
      unidentifiedErrors.push_back(i);
    }
    i++;
  }
}

json BatchResponse::getResult(long id) {
  if (responseIndex.find(id) != responseIndex.end()) {
    return response[responseIndex[id]][JSONRPCCPP_RESULT];
  } else {
    return json::object();
  }
}

JsonRpcException BatchResponse::getError(long id) {
  if (errorIndex.find(id) != errorIndex.end()) {
    const json& error = response[errorIndex[id]];
    return JsonRpcException(error[JSONRPCCPP_ERROR][JSONRPCCPP_ERROR_CODE],
                            error[JSONRPCCPP_ERROR][JSONRPCCPP_ERROR_MESSAGE]);
  } else {
    return JsonRpcException(0, "");
  }
}

bool BatchResponse::containsErrors() { return errors; }