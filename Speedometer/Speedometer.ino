#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <WifiConnect.h>
#include <WebSock.h>
#include "secret.h"

WifiConnect myWifi(SECRET_SSID, SECRET_PWD);
WebSock sock(FEEDER_IPV4_ADDRESS,3000);

const int IR_SENSOR_START_PIN = 2;
const int IR_SENSOR_END_PIN = 4;
const int BUZZER_PIN=8;
const long DISTANCE_BETWEEN_SENSOR = 30;

long timeTookByCarToCross = 0;
long startTime =0;
long endTime=0;
long speed = 0.0;
int lastRecordedSpeed = 0;

ArduinoLEDMatrix matrix;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //initiate UNO R4 LED matrix
  matrix.begin();

  //intiate connection to home wifi
  myWifi.init();

  //initate websocket connection to the feeder server
  sock.connect();

  // define pin modes for IR sensors and Indicator Buzzer/LED
  pinMode(IR_SENSOR_START_PIN, INPUT);
  pinMode(IR_SENSOR_END_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  //initialize Speedometer
  initializeSpeedoMeter();

  // indicate initialization is done
  initiationCompleteIndication();
}

void loop() {
  // when car crossed first sensor
  int didCarCrossStartSensor = digitalRead(IR_SENSOR_START_PIN);

  // when car crossed second sensor
  int didCarCrossEndSensor = digitalRead(IR_SENSOR_END_PIN);

  // if car is detected at first sensor, record start time in ms
  if (didCarCrossStartSensor == 0){
    // initialize all variables to zero for next reading
    initializeSpeedoMeter();
    buzzOn();
    startTime = millis();
  }

  // if car is detected at second sensor, record end time in ms
  if(didCarCrossEndSensor == 0 && startTime > 0){
    endTime = millis();

    // take the difference of start and end time
    timeTookByCarToCross = endTime - startTime;

    // calculate speed by distance / time
    calculateAndDisplaySpeed(timeTookByCarToCross);
    
    // send the speed to the server
    sendSpeedValueToFeederServer(speed);
    
    // turn of the reading indicator
    buzzOff();
    
    // log stats to serial port
    displayStats();

    // initialize all variables to zero for next reading
    initializeSpeedoMeter();
  }
}

// initialize all variables to zero for next reading
void initializeSpeedoMeter(){
  startTime = 0;
  endTime = 0;
  timeTookByCarToCross = 0;
  speed = 0.0;
}

// calculate the speed in cm/s
void calculateAndDisplaySpeed(long t){
  speed = (int)((DISTANCE_BETWEEN_SENSOR * 1000) / (t)) ;
  display(speed);
}

// display stats
// StartTime EndTime TimeDiff Speed cm/s
void displayStats(){
    Serial.print(startTime);
    Serial.print(" ");
    Serial.print(endTime);
    Serial.print(" ");
    Serial.print(timeTookByCarToCross);
    Serial.print(" ");
    Serial.print(speed);
    Serial.println(" cm/s");
}

// When number need to be displayed on Uno R4 LED Matrix
void display (long num){
  char buffer[10];
  itoa(num,buffer,10);
  display(buffer);
}

// Display on Uno R4 Wifi LED Matrix
void display(char text[]){
  matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);

  //add text
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();

  matrix.endDraw();
}

// Turn ON indicator - LED/Buzzer
void buzzOn(){
  digitalWrite(BUZZER_PIN, HIGH);
}

// Turn ON indicator - LED/Buzzer
void buzzOff(){
  digitalWrite(BUZZER_PIN,LOW);
}

// send the speed value to the server
void sendSpeedValueToFeederServer(int val){
  if(lastRecordedSpeed != val){
    sock.send(val);
    lastRecordedSpeed = val;
  }
}

void initiationCompleteIndication(){
  int icounter = 0;
  while (icounter <=3){
    buzzOn();
    delay(500);
    buzzOff();
    delay(500);
    icounter++;
  }
}