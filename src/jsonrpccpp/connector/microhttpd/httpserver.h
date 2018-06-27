#pragma once

#include <jsonrpccpp/connector/abstractserverconnector.h>
#include <microhttpd.h>
#include <map>

namespace jsonrpc {
/**
 * This class provides an embedded HTTP Server, based on libmicrohttpd, to
 * handle incoming Requests and send HTTP 1.1 valid responses. Note that this
 * class will always send HTTP-Status 200, even though an JSON-RPC Error might
 * have occurred. Please always check for the JSON-RPC Error Header.
 */
class HttpServer : public AbstractServerConnector {
 public:
  /**
   * @brief HttpServer, constructor for the included HttpServer
   * @param port on which the server is listening
   * @param enableSpecification - defines if the specification is returned in
   * case of a GET request
   * @param sslcert - defines the path to a SSL certificate, if this path is !=
   * "", then SSL/HTTPS is used with the given certificate.
   */
  HttpServer(int port, const std::string &sslcert = "", const std::string &sslkey = "");

  virtual bool StartListening();
  virtual bool StopListening();

 protected:
  bool virtual SendResponse(const std::string &response, void *addInfo = NULL);
  bool virtual SendOptionsResponse(void *addInfo);

 private:
  int port;
  bool running;
  std::string path_sslcert;
  std::string path_sslkey;
  std::string sslcert;
  std::string sslkey;

  struct MHD_Daemon *daemon;

  static int callback(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                      const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls);
};

}  // namespace jsonrpc
