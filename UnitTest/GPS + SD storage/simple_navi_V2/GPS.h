
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

const double target_lng = -94.581213;
const double target_lat = 39.099912;
const double pi = 3.14159265359;

double toRadian(double degree){
  return (degree / 360 * 2 * pi);
}

double toDegree(double radian){
  return (radian / 2 / pi * 360);
}

String longitude(){
  if (gps.location.isValid())
  {
    double temp =  gps.location.lng();
    String result = " l " + (String)temp + " l ";
    return result;
  } 
  return " no ";
}

String latitude() {
  if (gps.location.isValid())
  {
    double temp = gps.location.lat();
    String result = " k " + (String)temp + " k ";
    return result;
  } 
  return " no ";
}

String timeAndDate(){
  if (gps.date.isValid() && gps.time.isValid()){
    String result = String (gps.date.month()) + "/" + String (gps.date.day()) + "/" +
        String (gps.date.year()) + " " + String (gps.time.hour()) + ":" + String (gps.time.minute()) + ":" + String (gps.time.second());
        return result;
  } 
  return " INVALID ";
}

String distance(String lng_value, String lat_value){
  if (lng_value == " no "|| lat_value == " no "){
    return " distance INVALID ";
  }
  String result;
  double lat1 = toRadian( lat_value.toDouble() );
  double lng1 = toRadian( lng_value.toDouble() );
  double dlong = toRadian(target_lng) - lng1;
  double dlat = toRadian(target_lat) - lat1;
  double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(target_lat) * pow(sin(dlong / 2), 2);
  ans = 2 * asin(sqrt(ans));
  double R = 6371;
  ans = ans * R;
  result = "You have " + String(ans) +" km to go... ";
  return result; 
}

String bearing(String lng_value, String lat_value){
  String result;
  if (lng_value == " no " || lat_value == " no " ){
    return " bearing INVALID ";
  }
  double current_lat = lat_value.toDouble();
  double current_long = lng_value.toDouble();
  double X = (cos(toRadian(current_lat))) * (sin( toRadian( abs(current_long - target_lng) )));
  double Y = (cos(toRadian(current_lat)) * sin(toRadian(target_lat))) - (sin( toRadian(current_lat)) * 
    cos(toRadian(target_lat)) * cos ( toRadian( abs(current_long - target_lng) )));
  double bearing = atan2(X , Y);
  bearing = toDegree(bearing);
  if (bearing > 0 && bearing < 180){
    result = "Turn RIGHT heading: " + String(bearing) + " ";
  } else if (bearing > 180 && bearing < 360){
    result = "Turn LEFT heading: " + String(bearing) + " ";
  }
  return result;
}

String full(){
  return (String) longitude() + latitude() + timeAndDate() + distance( longitude() , latitude() ) + bearing( longitude(), latitude() );
}

char turn(String lng_value, String lat_value){
  if (lng_value == " no " || lat_value == " no " ){
    return 'X';
  }
  double current_lat = lat_value.toDouble();
  double current_long = lng_value.toDouble();
  double X = (cos(toRadian(current_lat))) * (sin( toRadian( abs(current_long - target_lng) )));
  double Y = (cos(toRadian(current_lat)) * sin(toRadian(target_lat))) - (sin( toRadian(current_lat)) * 
    cos(toRadian(target_lat)) * cos ( toRadian( abs(current_long - target_lng) )));
  double bearing = atan2(X , Y);
  bearing = toDegree(bearing);
  if (bearing > 0 && bearing < 180){
    return 'R';
  } else if (bearing > 180 && bearing < 360){
    return 'L';
  } else{
    return 'S';
  }
}


void displayInfo()
{
  Serial.print( (String) "long: " + longitude() );
  Serial.print( (String) "lat: " + latitude() );
  Serial.print((String) "time: " + timeAndDate() );
  //Serial.println();
  Serial.print( distance( longitude() , latitude() ));
  Serial.print( bearing( longitude(), latitude() ) ) ;
  Serial.println();
  //gps.location.isValid();
  
}
