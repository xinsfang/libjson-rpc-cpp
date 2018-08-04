#include "client.h"
#include "../constants.h"
#include "../exception.h"

using namespace jsonrpc;
using namespace std;
using json = nlohmann::json;

Client::Client(IClientConnector &connector, clientVersion_t version)
    : connector(connector), version(version), nextId(1) {}

bool VerifyResponse(const json &request, const json &response, clientVersion_t version) { return true; }

json Client::CallMethod(const string &name, const json &parameter) {
  json call;

  if (version == JSONRPC_CLIENT_V2) {
    call[JSONRPCCPP_VERSION] = "2.0";
  }
  call[JSONRPCCPP_METHOD] = name;
  call[JSONRPCCPP_PARAMS] = parameter;
  call[JSONRPCCPP_ID] = this->nextId++;

  try {
    json response = json::parse(connector.SendRPCMessage(call.dump()));
    if (VerifyResponse(call, response, this->version)) {
      return response[JSONRPCCPP_RESULT];
    }

  } catch (json::parse_error e) {
    throw JsonRpcException(ExceptionCode::ERROR_INVALID_JSON,
                           string("Failed to parse server response: ") + e.what());
  }
}

BatchResponse Client::CallProcedures(const BatchCall &calls) {

}
void Client::CallNotification(const std::string &name, const json &parameter) {
  json call;

  if (version == JSONRPC_CLIENT_V2) {
    call[JSONRPCCPP_VERSION] = "2.0";
  }
  call[JSONRPCCPP_METHOD] = name;
  call[JSONRPCCPP_PARAMS] = parameter;

  connector.SendRPCMessage(call.dump());
}

/*
void Client::CallMethod(const std::string &name, const json &parameter, json &result) {
  std::string request, response;
  protocol->BuildRequest(name, parameter, request, false);
  connector.SendRPCMessage(request, response);
  protocol->HandleResponse(response, result);
}

void Client::CallProcedures(const BatchCall &calls, BatchResponse &result) {
  std::string request, response;
  request = calls.toString();
  connector.SendRPCMessage(request, response);
  Json::Reader reader;
  json tmpresult;

  if (!reader.parse(response, tmpresult) || !tmpresult.isArray()) {
    throw JsonRpcException(Errors::ERROR_CLIENT_INVALID_RESPONSE, "Array expected.");
  }

  for (unsigned int i = 0; i < tmpresult.size(); i++) {
    if (tmpresult[i].isObject()) {
      json singleResult;
      try {
        json id = this->protocol->HandleResponse(tmpresult[i], singleResult);
        result.addResponse(id, singleResult, false);
      } catch (JsonRpcException &ex) {
        json id = -1;
        if (tmpresult[i].isMember("id")) id = tmpresult[i]["id"];
        result.addResponse(id, tmpresult[i]["error"], true);
      }
    } else
      throw JsonRpcException(Errors::ERROR_CLIENT_INVALID_RESPONSE, "Object in Array expected.");
  }
}

BatchResponse Client::CallProcedures(const BatchCall &calls) {
  BatchResponse result;
  this->CallProcedures(calls, result);
  return result;
}

json Client::CallMethod(const std::string &name, const json &parameter) {
  json result;
  this->CallMethod(name, parameter, result);
  return result;
}

void Client::CallNotification(const std::string &name, const json &parameter) {
  std::string request, response;
  protocol->BuildRequest(name, parameter, request, true);
  connector.SendRPCMessage(request, response);
}
*/