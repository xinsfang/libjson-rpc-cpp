#include "batchcall.h"
#include "../constants.h"

using namespace jsonrpc;
using namespace std;
using json = nlohmann::json;

BatchCall::BatchCall() : nextId(1), result(json::array()) {}

long BatchCall::addMethod(const std::string &methodname, json &params) {
  json call;
  call[JSONRPCCPP_VERSION] = "2.0";
  call[JSONRPCCPP_METHOD] = methodname;
  call[JSONRPCCPP_PARAMS] = params;
  call[JSONRPCCPP_ID] = this->nextId;

  result.push_back(call);
  return this->nextId++;
}
void BatchCall::addNotification(const std::string &methodname, json &params) {
  json call;
  call[JSONRPCCPP_VERSION] = "2.0";
  call[JSONRPCCPP_METHOD] = methodname;
  call[JSONRPCCPP_PARAMS] = params;
  result.push_back(call);
}

const json& BatchCall::getCall() const { return result; }