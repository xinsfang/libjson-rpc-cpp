#pragma once

#include <memory>
#include <string>
#include <vector>
#include "iclientconnectionhandler.h"

namespace jsonrpc {
  class AbstractServerConnector {
   public:
    virtual ~AbstractServerConnector() {}

    void AddConnectionHandler(IClientConnectionHandler& handler) { connectionHandlers.push_back(&handler); }

    virtual bool StartListening() = 0;
    virtual bool StopListening() = 0;

    std::string ProcessRequest(const std::string& request) {
      std::string result = "";
      for (auto handler : connectionHandlers) {
        result = handler->HandleRequest(request);
        if (result != "") {
          return result;
        }
      }
      return result;
    }

   private:
    std::vector<IClientConnectionHandler*> connectionHandlers;
  };
}