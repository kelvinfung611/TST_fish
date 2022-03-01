/* Connection:
    EN : 5V
    Ain: pinMode Output
    GND : Ground
*/
#define ENCA 3 // ORANGE
#define ENCB 2 // BLUE
String cmd;
long int pos_Main;
  int level = 0;
  int idx = 9;
  int power = 0;

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
    cmd = Serial.readString();
    level = cmd[0] - '0';
    idx = cmd[1] - '0';
    Serial.println(level);
    Serial.println(idx);
    power = map(level,1,9,10,255);
    Serial.println(power);
  }
  //int power = map(level,1,9,10,255);
  

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

void readEncoder_Main(){
 int b_A = digitalRead(ENCB);
  if(b_A > 0){
    pos_Main++;
  }
  else{
    pos_Main--;
  }
}
