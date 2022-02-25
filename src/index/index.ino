#include "SPI.h"
#include "tft_screen.h"
#include "button.h"
#include "communication.h"
int volts = 12.345;
int amps = 11.234;
int sp = 10.000;
int temperature = 30.0;
int turnVal = 9;
int power = 9;
int xMap = 3;
int yMap = 6;
int pos_main = 0;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial2.begin(9600);
  init_button();
  init_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  receive(temperature,volts,amps,sp);
  eventListener(turnVal,power);
  render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);

}
