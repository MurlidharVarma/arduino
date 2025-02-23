#ifndef OledGrid_h
#define OledGrid_h

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OledGrid{

  private:
    int _textSize = 2;
    String _n11;
    String _n12;
    String _n21;
    String _n22;
    void printGrid();

  public:
    void init();
    void clear();
    void show(String str);
    void show(int num);
    void size(int size);
    void grid(int n11, int n12, int n21, int n22);
    void grid(String n11, String n12, String n21, String n22);
    void grid(String n11, String n12, int n21, int n22);
    void grid(String n11, int n12, String n21, int n22);
    void grid(int n11, String n12, int n21, String n22);
};

#endif