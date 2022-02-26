//https://www.igismap.com/formula-to-find-bearing-or-heading-angle-between-two-points-latitude-longitude/




void setup() {
  // GPS: (Latitude, longitude)
  //Heading from A to B = atan2(X,Y)
  // X = cos(B_latitude) * sin( abs( A_longitude - B_longitude) *in degree*
  // Y = cos(A_latitude) * sin(B_latitude) - sin(A_latitude) * cos(B_latitude) * cos ( abs(A_longitude - B_longitude) ) *in degree*
  
  // radians to degree : radians / 2 / pi * 360
  // degree to radians: degrees / 360 * 2 * pi

  Serial.begin(9600);
}

const double pi = 3.14159265359;

double toRadian(double degree){
  return (degree / 360 * 2 * pi);
}

double toDegree(double radian){
  return (radian / 2 / pi * 360);
}
  
void loop() {
  // put your main code here, to run repeatedly:
  double A_lat = 39.099912;
  double B_lat = 38.627089;
  double A_long = -94.581213;
  double B_long = -90.200203;

  double X = (cos(toRadian(A_lat))) * (sin( toRadian( abs(A_long - B_long) )));
  double Y = (cos(toRadian(A_lat)) * sin(toRadian(B_lat))) - (sin( toRadian(A_lat)) * cos(toRadian(B_lat)) * cos ( toRadian( abs(A_long - B_long) )));
  double bearing = atan2(X , Y);
  bearing = toDegree(bearing);
  if (bearing > 0 && bearing < 180){
    Serial.println((String) "Turn RIGHT heading: " + bearing);
  } else if (bearing > 180 && bearing < 360){
    Serial.println((String) "Turn LEFT heading: " + bearing);
  }
  

}
