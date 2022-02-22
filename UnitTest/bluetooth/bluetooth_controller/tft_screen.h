//#include "PDQ_GFX.h"
//#include "PDQ_ILI9341.h"
//#define  ILI9340_CS_PIN    10      // <= /CS pin (chip-select, LOW to get attention of ILI9340, HIGH and it ignores SPI bus)
//#define ILI9340_DC_PIN    9     // <= DC pin (1=data or 0=command indicator line) also called RS
// other PDQ library options
//#define  ILI9340_SAVE_SPCR 0     // <= 0/1 with 1 to save/restore AVR SPI control register (to "play nice" when other SPI use)
//PDQ_ILI9341 tft;
//#define libName "PDQ_GFX library"
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
  delay(2500);
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
  tft.print("    ");
  tft.print(xMap);
  tft.print(", ");
  tft.println(yMap);
  
  tft.setTextSize(2);
  tft.setCursor(20, 198);
  tft.print("       ");
  tft.println(power);

  delay(200);
}
