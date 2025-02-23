#include <OledGrid.h>
#include <WifiConnect.h>
#include <WebSock.h>
#include "secret.h"

OledGrid oled;

// defines pins numbers
const int TRIGGER_PIN = 9;
const int ECHO_PIN = 10;

const boolean isDisplay = false;

// defines variables
long duration;
int distance;

WifiConnect myWifi(SECRET_SSID, SECRET_PWD);
WebSock sock(FEEDER_IPV4_ADDRESS,4000);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input


  //intiate connection to home wifi
  myWifi.init();

  //initate websocket connection to the feeder server
  sock.connect();

  if(isDisplay){
    Serial.begin(9600); // Starts the serial communication
    oled.init();
    oled.size(5);
    oled.clear();
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  // Speed of Sound => 340m/s or 34cm/ms or 0.034cm/microsec
  distance = duration * 0.034 / 2;

  if(isDisplay){
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    oled.clear();
    oled.show(distance);
  }

  sock.send(distance);
  delay(1000);
}
