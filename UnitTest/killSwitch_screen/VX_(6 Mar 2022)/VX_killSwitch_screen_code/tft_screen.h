#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#define libName "Adafruit library"

void init_screen(){
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 46);
  tft.println("starting");
  //delay(2500);
  tft.fillScreen(ILI9341_WHITE);
}

void render(int volts, int amps, int sp, int temperature, int turnVal, int power, int xMap, int yMap, int pos_main){
  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.print(volts);
  tft.println(" V");
  tft.setTextSize(3);
  tft.setCursor(20, 40);
  tft.print(amps);
  tft.println(" A");
  tft.setTextSize(3);
  tft.setCursor(20, 70);
  tft.print(sp);
  tft.println(" km/h");
  tft.setTextSize(3);
  tft.setCursor(20,100);
  tft.println(temperature);
  tft.setTextSize(3);
  tft.setCursor(20,130);
  tft.println(pos_main);

  tft.setTextSize(2);
  tft.setCursor(20, 158);
  tft.print("SET   ");
  tft.print("turnVal: ");
  tft.println(turnVal);
  tft.setCursor(20,178);
  tft.print("       ");
  tft.print((String)"("+xMap+","+yMap+")");
  
  tft.setTextSize(2);
  tft.setCursor(20, 198);
  tft.print("       ");
  tft.println(power);

  delay(200);
}
