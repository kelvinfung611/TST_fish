/*
 * simple sd card storage test
 * GND to GND
 * VCC to 5V
 * CS to pin 10
 * SCK to pin 13
 * MOSI to pin 11
 * MISO to pin 12
 */

#include <SPI.h>
#include <SD.h>
File myFile;


String filename = "";

void setName(String text){
  filename = text;
  Serial.println(filename);
}

void SD_card_init(){
  
   if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
    }
   
   Serial.println("storing...");
  myFile = SD.open(filename, FILE_WRITE);
    myFile.println("Data: "); // for testing only
    myFile.close();
}

void store(String message) {
  Serial.println("storing...");
  myFile = SD.open(filename, FILE_WRITE);
   myFile.println(message);
    myFile.close();
}
