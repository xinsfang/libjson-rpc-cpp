/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    mockclientconnectionhandler.h
 * @date    10/29/2014
 * @author  Peter Spiess-Knafl <dev@spiessknafl.at>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_MOCKCLIENTCONNECTIONHANDLER_H
#define JSONRPC_CPP_MOCKCLIENTCONNECTIONHANDLER_H

#include "../iclientconnectionhandler.h"
#include <string>

namespace jsonrpc
{
    class MockClientConnectionHandler : public IClientConnectionHandler
    {
        public:
            MockClientConnectionHandler();

            virtual std::string HandleRequest(const std::string& request);

            std::string response;
            std::string request;
            long timeout;
    };


}
#endif // JSONRPC_CPP_MOCKCLIENTCONNECTIONHANDLER_H
