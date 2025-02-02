#include "Arduino.h"
#include <WiFiS3.h>

#include "HttpConnect.h"

HttpConnect::HttpConnect(char* host, int port){
  _host = host;
  _port = port;
  _hostStr = String(host);
}

void HttpConnect::get(String path){
  call("GET", path, "NULL");
}

void HttpConnect::post(String path, String payload){
  call("POST", path, payload);
}

void HttpConnect::put(String path, String payload){
  call("PUT", path, payload);
}

void HttpConnect::call(String method, String path, String payload){
    String response="";
    String request="";
    
    // Connect to the server
    if (!_client.connect(_host, _port)) {
      Serial.println("Connection to server failed");
      return;
    }

    request = method+" " + path + " HTTP/1.1\r\n" + "Host: " + _hostStr + "\r\n" + "Content-Type: application/json\r\n";
    
    if(payload == "NULL"){
      request = request + "Connection: close\r\n\r\n";
    }else{
      request = request + "Content-Length: " + payload.length() + "\r\n" + "Connection: close\r\n\r\n" + payload;
    }

    // Debugging output
    Serial.println(path);
    // Send the request
    _client.print(request);

    // delay(1000);
    _client.stop();

    // Close the connection
    // _client.stop();
    // Serial.println("_client closed");

    // return response;
}

void HttpConnect::readResponse(){
      while (_client.available()) {
      String line = _client.readString();
      Serial.print(line);
    }
}