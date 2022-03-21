#include "GPS.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
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

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); 
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(longitude());
  Serial.print(latitude());
  Serial.print(timeAndDate());
  Serial.println();
  Serial.print( distance( longitude() , latitude() ));
  Serial.print( bearing( longitude(), latitude() ) ) ;
  
}
