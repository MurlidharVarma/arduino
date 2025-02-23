#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledGrid.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void OledGrid::init(){
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextColor(WHITE);  
}

void OledGrid::show(String str){
  display.setTextSize(_textSize); 
  display.setCursor(0,10); 
  display.println(str);
  display.display();
}

void OledGrid::show(int num){
  display.setTextSize(_textSize); 
  display.setCursor(20,10); 
  display.println(num);
  display.display();
}

void OledGrid::clear(){
  display.clearDisplay();
}

void OledGrid::grid(int n11, int n12, int n21, int n22){
  _n11 = String(n11);
  _n12 = String(n12);
  _n21 = String(n21);
  _n22 = String(n22);
  printGrid();
}

void OledGrid::grid(String n11, String n12, String n21, String n22){
  _n11 = n11;
  _n12 = n12;
  _n21 = n21;
  _n22 = n22;
  printGrid();
}

void OledGrid::grid(String n11, String n12, int n21, int n22){
  _n11 = n11;
  _n12 = n12;
  _n21 = String(n21);
  _n22 = String(n22);
  printGrid();
}
void OledGrid::grid(String n11, int n12, String n21, int n22){
  _n11 = n11;
  _n12 = String(n12);
  _n21 = n21;
  _n22 = String(n22);
  printGrid();
}
void OledGrid::grid(int n11, String n12, int n21, String n22){
  _n11 = String(n11);
  _n12 = n12;
  _n21 = String(n21);
  _n22 = n22;
  printGrid();
}

void OledGrid::printGrid(){
  display.setTextSize(_textSize); 
  display.drawLine(64,0,64,64, WHITE);
  display.drawLine(0,32,128,32, WHITE);
  display.setCursor(2,10); 
  display.println(_n11);
  display.setCursor(70,10); 
  display.println(_n12);
  display.setCursor(2,40); 
  display.println(_n21);
  display.setCursor(70,40); 
  display.println(_n22);
  display.display();
}

void OledGrid::size(int size){
  _textSize = size;
}