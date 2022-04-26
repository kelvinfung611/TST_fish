String c;
String cmd;
bool check;
int ascii_sum;
char incomingByte;
long long timer1 = 0;
char message [10];
// int A_current;
// int voltage;
// int motor_rpm;
// int speed_now;

bool checkSum(char incomingByte, int siglen, char cmd[]) {
      return true; // here is the hard code
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

void transmit(int xMap, int yMap, int tMap, int pMap){
  if(millis() - timer1 > 200){
    timer1 = millis();

    ascii_sum = 'R' + (xMap + '0')+'U' + (yMap + '0')+'T' + (tMap + '0')+'P' + (pMap + '0');
    String sum_str = "R" + String(xMap) +"U"+ String(yMap)+"T" + String(tMap) +"P"+ String(pMap) + String(ascii_sum) + "$"; //payload + checksum
    strcpy(message,sum_str.c_str());
    Serial1.write(message);
  }
}

void receiving(int & temperature, int & voltage, int & current, int & rpm,  bool &time_update,unsigned last_cmd_time, char &heading){
    if (Serial1.available()>0){
    while(incomingByte != '!'){
    
      incomingByte = Serial1.read();
      if ((unsigned)(millis() - last_cmd_time) > (unsigned) 5000){
            break;
          } 
      }
      }
      
      incomingByte = Serial1.read();
      char cmd[21];
      int siglen = -1;
      while (incomingByte != '$' and siglen < 21) {  //read char by char until we know the end of signal is reached indicated by the identifier '$'
        if (Serial1.available()>0){
           cmd[siglen] = incomingByte;
          siglen++;
          incomingByte = Serial1.read();
  
        }
        if ((unsigned)(millis() - last_cmd_time) > (unsigned) 5000){
            break;
          }
      }
      if (Serial1.available()>60){
        while (Serial1.available()>0){
          Serial1.read(); 
           if ((unsigned)(millis() - last_cmd_time) > (unsigned) 5000){
            break;
          }  
        }
      }
      //cmd[11] = '\0';
      //Serial.println(cmd);
      check = checkSum(incomingByte, siglen, cmd);
      if (check == true) {
        
        String raw_tem = String(cmd[1]); //used to be speed_now
        temperature = raw_tem.toInt();
        String raw_vol = String(cmd[3])+ String(cmd[4]) + String(cmd[5]);
        voltage = raw_vol.toInt();
        String raw_current = String(cmd[7])+ String(cmd[8]) + String(cmd[9]);
        current = raw_current.toInt();
        String raw_rpm = String(cmd[11])+ String(cmd[12]) + String(cmd[13]);
        rpm = raw_rpm.toInt();
        heading = cmd[19];
        Serial.println((String) temperature + " " + voltage + " " + current + " " + rpm + " " + heading);
        
      } else{
        //error msg
      }
      
     }
