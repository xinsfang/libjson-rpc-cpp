#include "client.h"

using namespace jsonrpc;
using json = nlohmann::json;

Client::Client(IClientConnector &connector, clientVersion_t version) : connector(connector) {}

nlohmann::json Client::CallMethod(const std::string &name, const json &parameter) {}
BatchResponse Client::CallProcedures(const BatchCall &calls) {}
void Client::CallNotification(const std::string &name, const json &parameter) {}

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