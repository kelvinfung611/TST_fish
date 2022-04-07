#include "SPI.h"
#include "tft_screen.h"
#include "gamepad.h"
int volts = 12;
int amps = 11;
int sp = 10;
int temperature = 30;
int turnVal = 0;
int power = 0;
int xMap = 4;
int yMap = 4;
int pos_main = 0;
long long timer = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  init_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Update control variables from buttons
  //Reading Joystick Value
  eventListener(xMap,yMap,turnVal,power);
  if(millis() - timer > 100){
    timer = millis();
    render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);
  }
  //render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);

}
