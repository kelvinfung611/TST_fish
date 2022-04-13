// protocol example: R9U9T9P0531?
#define pwm_Pin1 5
#define ENCA 3 // ORANGE
#define ENCB 2 // BLUE
char c;
int idx = 0;
char cmd [12];
bool check = false;
int xMap,yMap,turnVal,power = 0;
long long killTimer = 0;
long long pos_Main;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
   pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(ENCA), readEncoder_Main, RISING);
  pinMode(pwm_Pin1,OUTPUT);
}

void loop() {
  int tem = (pos_Main % 2500) + 1;
  // put your main code here, to run repeatedly:
  if(Serial1.available() > 0){
  while (c != 'R'){ //read until R
    c = Serial1.read();
  }
  delay(20);
  idx = 0;
  while(idx < 11 and c != '?'){
    cmd[idx] = c;
    c = Serial1.read();
    idx++;
  }
  cmd[11] = '\0';
  check = checkSum(idx, cmd);
  if(check){
    update();
    killTimer = millis();
    Serial.print(xMap);
    Serial.print(yMap);
    Serial.print(turnVal);
    Serial.print(power);
    Serial.println();
  }else{
    Serial.println("fail");
  }
  }
  killswitch();
  if (turnVal == 7){
    
    if (tem > 1250 && tem < 2500){
      
      analogWrite(5,(power*255)/9) ;
      
    } else{
      
      analogWrite(5,((power*255)/9) / 4);
      
    }
    
  } else if (turnVal == 8){
    
      if (tem > 1250 && tem < 2500){
        
        analogWrite(5, ((power*255)/9) / 4) ;
      } else {
        
        analogWrite(5,(power*255)/9);
        
      }
  } else if (turnVal == 9) {
    
    analogWrite(5,(power*255)/9);
    
  } else{

    analogWrite(5,0);
  }
    }


bool checkSum(int siglen, char cmd[]) {
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


void killswitch(){
   if (millis() - killTimer > 3000) {
    analogWrite (pwm_Pin1, 0);
    Serial.println("Kill switch activated"); 
  }
}

void update(){
  String w = String(cmd);
  xMap = String(w.substring(1, 2)).toInt();
  yMap = String(w.substring(3, 4)).toInt();
  turnVal = String(w.substring(5, 6)).toInt();
  power = String(w.substring(7, 8)).toInt();
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
