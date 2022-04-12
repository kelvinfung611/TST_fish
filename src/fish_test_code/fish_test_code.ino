/* Connection:
    EN : 5V
    Ain: pinMode Output
    GND : Ground
*/
#define ENCA 3 // ORANGE
#define ENCB 2 // BLUE
#define pwm_Pin1 5
String cmd;
long int pos_Main;
int level = 0;
int idx = 9;
int power = 0;
long long killTimer;
char incomingByte = '0';
bool check = false;
String w;

void setup() {
  Serial.begin(9600); //change to 115200 if you want to
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(ENCA), readEncoder_Main, RISING);
  pinMode(5,OUTPUT);
  Serial.println("Arming........");

}

void loop() {
  int tem = (pos_Main % 2500) + 1; 
  //Serial.println(pos_Main);
  if (Serial.available() > 0){
    while(incomingByte != 'R'){
      incomingByte = Serial.read();
    }
    Serial.print(incomingByte);
    char cmd[12];
    int siglen = 0;
    while(incomingByte != '?' and siglen < 11){
      cmd[siglen] = incomingByte;
      siglen++;
      incomingByte = Serial.read();
      Serial.print(incomingByte);
    }
    while(Serial.available()>0){
      Serial.read();
    }
    cmd[11] = '\0';
    check = checkSum(incomingByte, siglen, cmd);
    if(check){
      killTimer = millis();

      w = String(cmd);
      Serial.print(w[1]);
      Serial.print(w[3]);
      Serial.println();
    if (idx == 7){
    
    if (tem > 1250 && tem < 2500){
      
      analogWrite(5,power) ;
      
    } else{
      
      analogWrite(5,power / 4);
      
    }
    
  } else if (idx == 8){
    
      if (tem > 1250 && tem < 2500){
        
        analogWrite(5, power / 4) ;
      } else {
        
        analogWrite(5,power);
        
      }
  } else if (idx == 9) {
    
    analogWrite(5,power);
    
  } else{

    analogWrite(5,0);
  }
    }
    else{
      Serial.println("rejected");
    }
    killswitch();
  }
  //int power = map(level,1,9,10,255);
}

void readEncoder_Main(){
 int b_A = digitalRead(ENCB);
  if(b_A > 0){
    pos_Main++;
  }
  else{
    pos_Main--;
  }
}

void killswitch(){
   if (millis() - killTimer > 3000) {
    analogWrite (pwm_Pin1, 0);
    Serial.println("Kill switch activated"); 
  }
}

bool checkSum(char incomingByte, int siglen, char cmd[]) {
  check = false;
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
