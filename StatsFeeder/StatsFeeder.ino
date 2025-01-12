#include "secret.h"
#include "WifiConnect.h"
#include "WebSock.h"

WifiConnect myWifi(SECRET_SSID, SECRET_PWD);
WebSock sock("192.168.1.4",3000);

int lastData = 0;

int COUNTER = 10;

void setup() {
  Serial.begin(9600);
  myWifi.init();
  sock.connect();
}

void loop() {
  // put your main code here, to run repeatedly:
  // myHttp.readResponse();
  if(COUNTER < 999){
    getData(COUNTER);
    COUNTER+=10;
    delay(10000);
  }
}

String getData(int val){
  if(lastData != val){
    sock.send(val);
    lastData = val;
  }
}
