#include "GPS.h"
#include "SD_card.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
//static const int RXPin = 4, TXPin = 3;
//static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
//TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

//File myFile;
//String file = "Test on: " + timeAndDate();

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  setName("data.txt");
  SD_card_init();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.available() > 0)
    if (gps.encode(ss.read()))
      String navi = full();
      Serial.println(full());
      store(full());

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
