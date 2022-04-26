#include "SPI.h"
#include "PDQ_GFX.h"
#include "PDQ_ILI9341_config.h"
#include "PDQ_ILI9341.h"
PDQ_ILI9341 tft;
#define libName "PDQ_GFX library"
//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h"
//#define TFT_DC 9
//#define TFT_CS 10
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
//#define libName "Adafruit library"

void init_screen(){
//    Serial.begin(115200);
//  while (!Serial);
//  
//#if defined(_PDQ_ILI9341H_)
//  Serial.println(F("PDQ ILI9341 2.2\" SPI TFT Test!     ")); 
//#else
//  Serial.println(F("Adafruit ILI9341 2.2\" SPI TFT Test!")); 
//#endif
// 
#if defined(ILI9341_RST_PIN)  // reset like Adafruit does
  FastPin<ILI9341_RST_PIN>::setOutput();
  FastPin<ILI9341_RST_PIN>::hi();
  FastPin<ILI9341_RST_PIN>::lo();
  delay(1);
  FastPin<ILI9341_RST_PIN>::hi();
#endif

  tft.begin();      // initialize LCD
  tft.setRotation(1);
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 46);
  tft.println("starting");
  delay(2500);
}

void render(int volts, int amps, int sp, int temperature, int turnVal, int power, int xMap, int yMap, int pos_main, char heading){
  tft.setTextSize(3);
  tft.setCursor(20, 10);
  tft.print(volts);
  tft.print(" V");
    
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
  tft.print(power);
  tft.print("   Please turn:");
  tft.println(heading);


  //delay(200);
}
