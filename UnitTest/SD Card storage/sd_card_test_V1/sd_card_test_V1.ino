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


String input = "";

void setup() {
  // put your setup code here, to run once:
  // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
    
    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
    }
    Serial.println("initialization done.");
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open("test.txt", FILE_WRITE);
    myFile.println("this is a test file"); // for testing only
    myFile.close();
    
}

void loop() {
  // put your main code here, to run repeatedly:
  now = millis();
  if (Serial.available() > 0){
    myFile = SD.open("test.txt", FILE_WRITE);
    input = Serial.readString();
    if(input.length() >= 5){
      myFile.close();
      Serial.println("closed");
      while(1);
    }
    
    myFile.println(input);
    myFile.close();
    Serial.println((String) "You have stored: " + input);
  }
  
}
