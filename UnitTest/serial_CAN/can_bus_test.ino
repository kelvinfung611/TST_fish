#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>

int current_speed = 0;
int current_temperature = 0;
int current_voltage = 0;
int current_current = 0;

#define can_tx 2
#define can_rx 3

Serial_CAN can;

//CAN.send(id,1,16,data) where 1 indicates extended frame

int hexadecimalToDecimal(String hexVal)
{
    int len = hexVal.length();
 
    // Initializing base value to 1, i.e 16^0
    int base = 1;
 
    int dec_val = 0;
 
    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
 
            // incrementing base by power
            base = base * 16;
        }
 
        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;
 
            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}

void setup() 
{
  Serial.begin(9600);
  while(!Serial); //wait for the serial got ready
  can.begin(can_tx, can_rx, 9600);
  if(can.canRate(CAN_RATE_250)) //setting the can baud rate
  {
    Serial.println("set can rate ok");  
  }
  else
  {
    Serial.println("set can rate fail"); 
   }
   

}

void loop() 
{
  if(millis()%1000 == 0){
    
    readAll();//called for every one seconds
    
    }
}

void getSpeed(){
  unsigned char data[8];
  data[0] = 0x40;
  data[1] = 0x01;
  data[2] = 0x21;
  data[3] = 0x01;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  //mcp2515.sendMessage(&frame);
  can.send(0x601,1,0,8,data);
  unsigned long id = 0;
  unsigned char inputMsg[8];
  //read until valid data come in  
  while (!can.recv(&id,inputMsg));
  
  String data1 = String(inputMsg[4]);
  String data2 = String(inputMsg[5]);
  String input = data1+data2;
  current_speed = hexadecimalToDecimal(input);
  Serial.print(current_speed);
}

void getTemperature(){
  //send the query out first
  unsigned char data[8];

  data[0] = 0x40;
  data[1] = 0x0F;
  data[2] = 0x21;
  data[3] = 0x01;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  //mcp2515.sendMessage(&frame);
  can.send(0x601,1,0,8,data);
  unsigned long id = 0;
  unsigned char inputMsg[8];
  //read until valid data come in  
  while (!can.recv(&id,inputMsg)); 
   
  String data1 = String(inputMsg[4]);
  String data2 = String(inputMsg[5]);
  String input = data1+data2;
  current_temperature = hexadecimalToDecimal(input);
  
  Serial.print(current_temperature);
}

void getVoltage(){
  unsigned char data[8];
  data[0] = 0x40;
  data[1] = 0x0D;
  data[2] = 0x21;
  data[3] = 0x01;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  can.send(0x601,1,0,8,data);
  unsigned long id = 0;
  unsigned char inputMsg[8];
  //read until valid data come in  
  while (!can.recv(&id,inputMsg)); 
  String data1 = String(inputMsg[4]);
  String data2 = String(inputMsg[5]);
  String data3 = String(inputMsg[6]);
  String data4 = String(inputMsg[7]);
  String input = data1+data2+data3+data4;
  current_voltage = hexadecimalToDecimal(input);
  Serial.print(current_voltage);
}

void getCurrent(){
  unsigned char data[8];
  data[0] = 0x40;
  data[1] = 0x00;
  data[2] = 0x21;
  data[3] = 0x01;
  data[4] = 0x00;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  can.send(0x601,1,0,8,data);
  unsigned long id = 0;
  unsigned char inputMsg[8];
  //read until valid data come in  
  while (!can.recv(&id,inputMsg));
  String data1 = String(inputMsg[4]);
  String data2 = String(inputMsg[5]);
  String input = data1+data2;
  current_current = hexadecimalToDecimal(input);
  Serial.print(current_current);
}

void readAll(){
  getSpeed();
  getTemperature();
  getCurrent();
  getVoltage();
  }
