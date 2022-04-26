#include "SPI.h"
#include "tft_screen.h"
#include "gamepad.h"
#include "communication.h"
//#include "SD_card.h"
//#include "GPS.h"

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

char heading = 'X';

unsigned long time_now;
unsigned long last_cmd_time = 0;
bool time_update = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  init_screen();
  //SD_card_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Update control variables from buttons
  //Reading Joystick Value
  eventListener(xMap,yMap,turnVal,power);
  //transmit(xMap,yMap,turnVal,power);
  receiving(temperature,volts,amps,sp, time_update,last_cmd_time,heading);
  if (time_update == true){
    last_cmd_time = time_now;
  }
  if(millis() - timer > 100){
    timer = millis();
    //may store message into SD card
    render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main,heading);
  }
  //render(volts,amps,sp,temperature,turnVal,power,xMap,yMap,pos_main);
  //killSwitch(last_cmd_time);
}

void killSwitch(unsigned last_cmd_time){
  if ((unsigned)(millis() - last_cmd_time) > (unsigned) 10000){
    
      tft.fillScreen(ILI9341_RED);
      tft.setTextSize(2);
      tft.setCursor(20, 46);
      tft.println("KILLED !");
      tft.println("enter 'R' to start again");
      Serial.println("Enter 'R' to restared");
      char restarted ;
      restarted = Serial.read();
      
      while (restarted != 'R'/*the joystick is not pressed*/)
      {
        restarted = Serial.read();
        last_cmd_time = time_now;
      }
      last_cmd_time = time_now;
      //tft.fillScreen(ILI9341_BLACK);
  }
}
