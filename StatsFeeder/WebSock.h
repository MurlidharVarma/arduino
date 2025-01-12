#ifndef WebSock_h
#define WebSock_h
#include <WebSocketClient.h>

using namespace net;

class WebSock {

  private:
    char* _host;
    uint16_t _port;
    bool _connected;

  protected:
    WebSocketClient _client;

  public:
    WebSock(char* host, uint16_t port);
    void connect();
    void send(int val);
};

#endif