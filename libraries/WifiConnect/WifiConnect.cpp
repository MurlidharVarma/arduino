#include "WiFiClient.h"
#include "Arduino.h";
#include "WifiConnect.h";

WifiConnect::WifiConnect(char* ssid, char* pwd){
  _ssid = ssid;
  _pwd = pwd;
  _status = WL_IDLE_STATUS;
}

void WifiConnect::init(){
  checkIfWifiModuleExists();
  checkWifiFirmwareVersion();
  attemptWifiConnection();
}

String WifiConnect::status(){
  return _statusMsg;
}

// check for the WiFi module:
void WifiConnect::checkIfWifiModuleExists(){
  log("Checking if Wifi Module Exists");
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    log("No Wifi Module Exists");
    // don't continue
    while (true);
  }
  log("Checked Wifi Module Exists");
}

// check for latest firmware Version
void WifiConnect::checkWifiFirmwareVersion(){
  log("Checking Wifi Module firmware version");
  String version = WiFi.firmwareVersion();
  if (version < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware. Current version: "+version+" New version: "+WIFI_FIRMWARE_LATEST_VERSION);
  }else{
    Serial.println("Wifi Firmware version: "+version);
  }
  log("Checked Wifi Module firmware version");

}

// attempt to connect to WiFi network:
void WifiConnect::attemptWifiConnection(){
  int attemptCount = 1;

  while (_status != WL_CONNECTED) {
    attemptCount++;
    log("Attempting Wifi Connection: #" + String(attemptCount));

    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(_ssid);
    // Connect to WPA/WPA2 network:
    _status = WiFi.begin(_ssid, _pwd);

    // wait 10 seconds for connection:
    delay(10000);
  }
  log("Established Wifi Connection");
  info();
}

void WifiConnect::info() {
  // print device IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}

void WifiConnect::log(String msg){
  _statusMsg = msg;
  Serial.println(msg);
}
