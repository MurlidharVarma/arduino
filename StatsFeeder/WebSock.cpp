#include <Arduino.h>
#include "WebSock.h"
#include <WebSocketClient.h>


using namespace net;
WebSock::WebSock(char* host, uint16_t port){
  _host = host;
  _port = port;
  _connected = false;
}

void WebSock::connect(){

  _client.onOpen([](WebSocket &ws) {
      Serial.println("Connected to websocket server");
  });

  _client.onClose([](WebSocket &ws, const WebSocket::CloseCode code,
                   const char *reason, uint16_t length) {
    Serial.println("Connection closed");
  });

  _client.onMessage([](WebSocket &ws, const WebSocket::DataType dataType,
                     const char *message, uint16_t length) {
    Serial.print("Got Message: ");
    Serial.println(message);
  });

  Serial.println("Connecting to websocket server");
  _connected = _client.open(_host,_port,"/");
  Serial.println("Sent connect request");
}


void WebSock::send(int val){
    char cStr[3];       // number of digits + 1 for null terminator
    itoa(val, cStr, 10);  // int value, pointer to string, base number

  _client.send(WebSocket::DataType::TEXT, cStr, 3);
}