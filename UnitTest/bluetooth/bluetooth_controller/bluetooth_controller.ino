#include "SPI.h"
#include "tft_screen.h"
//#include "button.h"
//#include "communication.h"
int volts = 12.345;
int amps = 11.234;
int sp = 10.000;
int temperature = 30.0;
int turnVal = 9;
int power = 9;
int xMap = 0;
int yMap = 0;
int pos_main = 0;
int x = 60;
int y = 60;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  //Serial2.begin(9600);
  //init_button();
  init_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //receive(temperature,volts,amps,sp);
  //eventListener(turnVal,power);
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 3){
    x = Serial1.read();
    delay(10);
    y = Serial1.read();
    delay(10);
      // Makes sure we receive corrent values
  if (x > 60 & x < 220) {
    xMap = map(x, 220, 60, 9, 0); // Convert the smartphone X and Y values to 0 - 1023 range, suitable motor for the motor control code below
  }
  if (y > 60 & y < 220) {
    yMap = map(y, 220, 60, 0, 9);
  }
    turnVal = Serial1.read();
    delay(10);
    power = Serial1.read();
  }
  if(xMap > 10){
    xMap = 10;
  }
  if(yMap > 10){
    yMap = 10;
  }
  if(xMap <= 0){
    xMap = 0;
  }
  if(yMap <= 0){
    yMap = 0;
  }
  render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);
  xMap = 0;
  yMap = 0;
  tft.clearDisplay();
  tft.fillScreen(ILI9341_WHITE);

}
