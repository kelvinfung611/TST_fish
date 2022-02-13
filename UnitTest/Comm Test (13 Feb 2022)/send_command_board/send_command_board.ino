void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String c;
String cmd;
bool check;
int ascii_sum;
String A_current;
String voltage;
String motor_rpm;
String speed_now;
char incomingByte;

// int A_current;
// int voltage;
// int motor_rpm;
// int speed_now;

bool checkSum(char incomingByte, int siglen, char cmd[]) {
  check = false;
  int cSum=0;
  for (int c=0; c < 15; c++){
    cSum+=cmd[c];
  }
  String numcheck = String(cmd[15]) + String(cmd[16]) + String(cmd[17]) + String(cmd[18]);
  int number = numcheck.toInt();
  //Serial.println(numcheck);
  //Serial.println (cSum);
  if (cSum == number) {
    check = true;
  }
  return check;
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("hi");
  if (millis() % 500 == 0 && millis() % 1000 != 0){
    ascii_sum = 'R' + '0' + 'U' + '0' + 'T' + '0' + 'P' + '0';
    Serial.println((String) "?R0U0T0P0" + ascii_sum + "/");

    if (Serial.available()>0){
    while(incomingByte != '!'){
    
      incomingByte = Serial.read();
      }
      incomingByte = Serial.read();
      char cmd[20];
      int siglen = 0;
      while (incomingByte != '$' and siglen < 20) {  //read char by char until we know the end of signal is reached indicated by the identifier '$'
        if (Serial.available()>0){
           cmd[siglen] = incomingByte;
          siglen++;
          incomingByte = Serial.read();
        }
      }
      if (Serial.available()>60){
        while (Serial.available()>0){
          Serial.read();   
        }
      }
      //cmd[11] = '\0';
      //Serial.println(cmd);
      check = checkSum(incomingByte, siglen, cmd);
      if (check == true) {
        
        speed_now = String(cmd[1]);
        //speed_now = data.toInt();
        voltage = String(cmd[3])+ String(cmd[4]) + String(cmd[5]);
        //voltage = data.toInt();
        A_current = String(cmd[7])+ String(cmd[8]) + String(cmd[9]);
        motor_rpm = String(cmd[11])+ String(cmd[12]) + String(cmd[13]);
        Serial.println((String) "Speed now: " + speed_now + " Voltage: " + voltage + " Current: " + A_current + " RPM: " + motor_rpm);
      } else{
        Serial.println("Failed");
      }
      
     }
  }
  
  
   if (millis() % 500 != 0 and millis() % 1000 == 0){
    ascii_sum = 'R' + '0' + 'U' + '0' + 'T' + '0' + 'P' + '0' ;
    Serial.println((String) "?R0U0T0P0" + ascii_sum + "/");
    ascii_sum = 'R' + '0' + 'U' + '0' + 'T' + '0' + 'P' + '0';
    Serial.println((String) "?R2U5T6P0" + ascii_sum + "/");

    if (Serial.available()>0){
    while(incomingByte != '!'){
    
      incomingByte = Serial.read();
      }
      incomingByte = Serial.read();
      char cmd[20];
      int siglen = 0;
      while (incomingByte != '$' and siglen < 20) {  //read char by char until we know the end of signal is reached indicated by the identifier '$'
        if (Serial.available()>0){
           cmd[siglen] = incomingByte;
          siglen++;
          incomingByte = Serial.read();
        }
      }
      if (Serial.available()>60){
        while (Serial.available()>0){
          Serial.read();   
        }
      }
      //cmd[11] = '\0';
      //Serial.println(cmd);
      check = checkSum(incomingByte, siglen, cmd);
      if (check == true) {
        
        speed_now = String(cmd[1]);
        //speed_now = data.toInt();
        voltage = String(cmd[3])+ String(cmd[4]) + String(cmd[5]);
        //voltage = data.toInt();
        A_current = String(cmd[7])+ String(cmd[8]) + String(cmd[9]);
        motor_rpm = String(cmd[11])+ String(cmd[12]) + String(cmd[13]);
        Serial.println((String) "Speed now: " + speed_now + " Voltage: " + voltage + " Current: " + A_current + " RPM: " + motor_rpm);
      } else{
        Serial.println("Failed");
      }
      
     }
  }
  
 
}
