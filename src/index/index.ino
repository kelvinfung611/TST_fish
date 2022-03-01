#include "SPI.h"
#include "tft_screen.h"
#include "button.h"
#include "communication.h"
int volts = 12;
int amps = 11;
int sp = 10;
int temperature = 30;
int turnVal = 9;
int power = 9;
int xMap = 3;
int yMap = 6;
int pos_main = 0;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  //Serial2.begin(9600);
  init_button();
  init_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Update control variables from buttons
  //Reading Joystick Value
  sensorValueX = analogRead(A8);
  sensorValueY = analogRead(A9);
  xMap = map(sensorValueX, 0, 1023, 0, 9);
  yMap = map(sensorValueY, 0, 1023, 0, 9);
  receive(temperature,volts,amps,sp);
  eventListener(turnVal,power);
  render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);
  transmit(xMap,yMap,turnVal,power);

}
