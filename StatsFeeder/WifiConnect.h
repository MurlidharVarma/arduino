#ifndef WifiConnect_h
#define WifiConnect_h

#include "Arduino.h"
#include <WiFiS3.h>

class WifiConnect{
  private:
    char* _ssid;
    char* _pwd;
    int _status;
    String _statusMsg;

  public:
    WifiConnect(char* ssid, char* pwd);
    void init();
    String status();
    void checkIfWifiModuleExists();
    void checkWifiFirmwareVersion();
    void attemptWifiConnection();
    void info();
    void log(String msg);
};

#endif