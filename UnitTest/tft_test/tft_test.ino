
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#define libName "Adafruit library"


float volts = 12.345;
float amps = 11.234;
float sp = 10.000;
float turnVal = 0.010;
int power = 9;
String coordinate = "(x,y)";
void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);

  tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);

  tft.setTextSize(2);
  tft.setCursor(20, 46);
  tft.println("starting");

  delay(2500);
  
  tft.fillScreen(ILI9341_WHITE);
}

void loop(void) {

  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.print(volts, 3);
  tft.println(" V");
  tft.setTextSize(3);
  tft.setCursor(20, 60);
  tft.print(amps, 3);
  tft.println(" A");
  tft.setTextSize(3);
  tft.setCursor(20, 110);
  tft.print(sp, 3);
  tft.println(" km/h");

  tft.setTextSize(2);
  tft.setCursor(20, 158);
  tft.print("SET   ");
  tft.print("turnVal: ");
  tft.println(turnVal,3);
  tft.setCursor(20,178);
  tft.print("       ");
  tft.print(coordinate);
  
  tft.setTextSize(2);
  tft.setCursor(20, 198);
  tft.print("       ");
  tft.println(power);

  delay(200);
}
