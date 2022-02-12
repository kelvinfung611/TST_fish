bool check;
char incomingByte = '0';
String w;
long int killTimer;
char message[20];

bool checkSum(char incomingByte, int siglen, char cmd[]) {
  check = false;
  //Serial.println("checking");
  int cSum=0;
  for (int c=0; c<8; c++){
    cSum+=cmd[c];
  }
  String numcheck = String(cmd[8]) + String(cmd[9]) + String(cmd[10]);
  int number = numcheck.toInt();
  ////Serial.println("Csum & number: ");
  ////Serial.println(cSum);
  ////Serial.println(number);
  if (cSum == number) {
    check = true;
  }
  return check;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()>0){
    while(incomingByte != 'R'){
    
      incomingByte = Serial.read();
      }
      char cmd[12];
      int siglen = 0;
      while (incomingByte != '?' and siglen<11) {  //read char by char until we know the end of signal is reached indicated by the identifier '?'
        if (Serial.available()>0){
           cmd[siglen] = incomingByte;
          siglen++;
          incomingByte = Serial.read();
          //Serial.print(incomingByte);
        }
      }
      //Empty out buffer
      if (Serial.available()>60){
        while (Serial.available()>0){
          Serial.read();   
        }
      }
      cmd[11] = '\0';
      check = checkSum(incomingByte, siglen, cmd);
      if (check == true) {
        //Timer for kill switch. Note: Keep it in checksum condition as we want it to resume operation once proper signlas are recived and not due to interfering signals.
        killTimer = millis();
        Serial.println("ok");
      }
  }
  killswitch();
}


void killswitch(){
   if (millis() - killTimer > 3000) {
    //Serial.println("Kill switch activated"); 
  }
}
//R9U9T9P91345?