#include "OledGrid.h"

OledGrid oled;
int counter = 0;

void setup() {
  oled.init();
  oled.size(5);
}

void loop(){
  // oledGrid.grid("Mass","Temp",counter, counter);
  oled.show(counter);
  counter++;
  delay(1000);
  oled.clear();
}