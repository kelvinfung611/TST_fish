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

unsigned long time_now;
unsigned long last_cmd_time = 0;
bool time_update = false;

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(9600);
  Serial.begin(9600);
  init_button();
  init_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Update control variables from buttons
  //Reading Joystick Value
  Serial.println("loop begin");
  
  time_now = millis();
  time_update = false;
  int sensorValueX = analogRead(A8);
  Serial.println("A8 read");
  int sensorValueY = analogRead(A9);
  Serial.println("A9 read");
  xMap = map(sensorValueX, 0, 1023, 0, 9);
  Serial.println("Xmap read");
  yMap = map(sensorValueY, 0, 1023, 0, 9);
  Serial.println("Ymap read");
  transmit(xMap,yMap,turnVal,power);
  Serial.println("transmitted");
  receive(temperature,volts,amps,sp, time_update,last_cmd_time);
  Serial.println("received");
  if (time_update == true){
    last_cmd_time = time_now;
  }
  eventListener(turnVal,power);
  Serial.println("button updated");
  render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);
  Serial.println("render");
  
  Serial.println(time_now - last_cmd_time);
  killSwitch(last_cmd_time);
  Serial.println("check end");
  

}
void killSwitch(long unsigned int & last_cmd_time){
  Serial.println("checking");
  if ((unsigned)(millis() - last_cmd_time) > (unsigned) 10000){
      tft.fillScreen(ILI9341_RED);
      tft.setTextSize(2);
      tft.setCursor(20, 46);
      tft.println("KILLED !");
      tft.println("enter 'R' to start again");
      Serial.println("Enter 'R' to restared");
      char restarted ;
      restarted = Serial.read();
      while (restarted != 'R')
      {
        restarted = Serial.read();
        last_cmd_time = time_now;
      }
      last_cmd_time = time_now;
      tft.fillScreen(ILI9341_BLACK);
  }
}
