#define upbutton 2
#define rightbutton 3
#define downbutton 4
#define leftbutton 5
int xMap,yMap,tMap,pMap,sensorValueX,sensorValueY = 0;
long long timer2, timer3, timer4 = 0;
String cmd = "*1234!";
int bounceDelay = 350;
char message [10];
int ascii_sum;
String sum_str;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  while (!Serial.read());
  while (!Serial1.read()); // Wait for serial to setup
  while (!Serial2.read()); // Wait for serial to setup
}

void loop(){
  sensorValueX = analogRead(A0);
  sensorValueY = analogRead(A1);
  xMap = map(sensorValueX, 0, 1023, 0, 9);
  yMap = map(sensorValueY, 0, 1023, 0, 9);


  //Reading the left, right, up and down buttons
  if((digitalRead(leftbutton) == LOW) && tMap > 1) {
    if (millis()-timer3 > bounceDelay){
      tMap--;
      timer3 = millis();
    }
  }
  else if ((digitalRead(rightbutton)== LOW) && tMap < 9) {
    if (millis()-timer3 > bounceDelay){
      tMap++;
      timer3 = millis();
    }
  }
  else if((digitalRead(downbutton) == LOW) && pMap > 0) {
    if (millis()-timer4 > bounceDelay){
      pMap--;
      timer4 = millis();
    }
  }
  else if ((digitalRead(upbutton)== LOW) && pMap < 9) {
    if (millis()-timer4 > bounceDelay){
      pMap++;
      timer4 = millis();
    }
  }
  if(millis() - timer2 > 200){
    timer2 = millis();
    cmd = updatedCmd();
    Serial.println(cmd);
    //strcpy(message, cmd.c_str());
    Serial1.print(cmd);
    Serial2.print(cmd);
    transmit();
  }
  
}

String updatedCmd(){
  String cmd = "*" + String(xMap) + String(yMap) + String(pMap) + String(tMap) + "!";
  return cmd;
}

void transmit(){
  
    ascii_sum = 'R' + (xMap + '0') + 'U' + (yMap + '0') + 'T' + (tMap + '0') + 'P' + (pMap + '0'); // Checksum
    sum_str = "R" + String(xMap) + "U" + String(yMap) + "T" + String(tMap) + "P" + String(pMap) + String(ascii_sum) + "?"; //payload + checksum
    strcpy(message, sum_str.c_str());
    Serial2.write(message);
    Serial.print("Signal: ");
    Serial.println(message);
    //blocking function, no need to wait for delay if use flush
    Serial2.flush();
}
