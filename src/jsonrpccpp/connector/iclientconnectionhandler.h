#pragma once

#include <string>

namespace jsonrpc {

class IClientConnectionHandler {
 public:
  virtual ~IClientConnectionHandler() {}
  virtual std::string HandleRequest(const std::string& request) = 0;
};

}  // namespace jsonrpc