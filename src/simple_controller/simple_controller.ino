#include "SPI.h"
#include "tft_screen.h"
#include "button.h"
int volts = 12.345;
int amps = 11.234;
int sp = 10.000;
int temperature = 30.0;
int turnVal = 9;
int power = 3;
int xMap = 3;
int yMap = 6;
int pos_main = 0;
int diff = 0;
long long timer1 = 0;
String output = "";
int sensorValueX = 0;
int sensorValueY = 0;
#define x_pin A8
#define y_pin A9
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  //Serial2.begin(9600);
  init_button();
  init_screen();
}

void loop() {
  button1.loop(); 
  button2.loop(); 
  button3.loop(); 
  button4.loop();
  sensorValueX = analogRead(x_pin);
  sensorValueY = analogRead(y_pin);
  xMap = map(sensorValueX, 0, 1023, 0, 9);
  yMap = map(sensorValueY, 0, 1023, 0, 9);
  diff = xMap - yMap;
  
  if(sensorValueY < 490){
    turnVal = 7;
  }
  else if(sensorValueY > 530){
    turnVal = 8;
  }else{
    turnVal = 9;
  }
  eventListener(turnVal,power);
  output = String(power) + String(turnVal);
  render(volts,amps,sp,temperature,turnVal,power,sensorValueX,sensorValueY,pos_main);
  Serial.println(output);
  if(millis()- timer1 > 200){
    timer1 = millis();
    Serial1.write(power);
    Serial1.write(turnVal);
  }

}
