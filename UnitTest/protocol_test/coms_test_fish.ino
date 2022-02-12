bool check;
char incomingByte = '0';
String w;
long int killTimer;
char message[20];
int temperature = 9;
int current = 9;
int voltage = 9;
int sp = 9;
int timer1 = 0;

bool checkSum(char incomingByte, int siglen, char cmd[]) {
  check = false;
  //Serial.println("checking");
  int cSum=0;
  for (int c=0; c<8; c++){
    cSum+=cmd[c];
  }
  String numcheck = String(cmd[8]) + String(cmd[9]) + String(cmd[10]);
  int number = numcheck.toInt();
  if (cSum == number) {
    check = true;
  }
  return check;
}


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  receiver(); //Serial port 1
  transmitter(); //Serial port 2
  killswitch();
}

void transmitter(){

if(millis() - timer1 > 200){ // send after every 200ms
  timer1 = millis();
  int ascii_sum = 'T' + (temperature + '0') + 'C' + (current + '0') + 'V' + (voltage + '0') + 'S' + (sp + '0');
  String sum_str = "T" + String(temperature) + "C" + String(current) + "V" + String(voltage) + "S" + String(sp) + String(ascii_sum);
  strcpy(message,sum_str.c_str());
  Serial2.write(message);
  Serial2.flush();
}
  }

void receiver(){
    if (Serial1.available()>0){
    while(incomingByte != 'R'){
    
      incomingByte = Serial1.read();
      }
      char cmd[12];
      int siglen = 0;
      while (incomingByte != '?' and siglen<11) {  //read char by char until we know the end of signal is reached indicated by the identifier '?'
        if (Serial1.available()>0){
           cmd[siglen] = incomingByte;
          siglen++;
          incomingByte = Serial1.read();
          //Serial.print(incomingByte);
        }
      }
      //Empty out buffer
      if (Serial1.available()>60){
        while (Serial1.available()>0){
          Serial1.read();   
        }
      }
      cmd[11] = '\0';
      check = checkSum(incomingByte, siglen, cmd);
      if (check == true) {
        //Timer for kill switch. Note: Keep it in checksum condition as we want it to resume operation once proper signlas are recived and not due to interfering signals.
        killTimer = millis();
        Serial1.println("ok");
      }
  }
  }

void killswitch(){
   if (millis() - killTimer > 3000) {
    //Serial.println("Kill switch activated"); 
  }
}
//R9U9T9P9559 example
//T9C9V9S9548 example of msg to be sent
