#ifndef HttpConnect_h
#define HttpConnect_h
#include "WifiConnect.h"
#include <WiFiClient.h>

class HttpConnect {

  private:
    WiFiClient _client;
    char* _host;
    String _hostStr;
    int _port;

  public:
    HttpConnect(char* host, int port);
    void call(String method, String path, String payload);
    void get(String path);
    void post(String path, String payload);
    void put(String path, String payload);
    void connectToWifi();
    void readResponse();
};

#endif