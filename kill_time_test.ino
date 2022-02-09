/* Connection:
    EN : 5V
    Ain: pinMode Output
    GND : Ground
*/
#define ENCA 3 // ORANGE
#define ENCB 2 // BLUE
String cmd;
long int pos_Main;
unsigned long time_now;
unsigned long last_cmd_time = 0;

  int level;
  int idx;
  bool warned = false;


void setup() {
  Serial.begin(115200);
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  attachInterrupt( digitalPinToInterrupt(ENCA), readEncoder_Main, RISING);
  pinMode(5,OUTPUT);
  Serial.println("Arming........");

}

void loop() {
  time_now = millis();
  int tem = (pos_Main % 2500) + 1; 
  int power;
  //Serial.println(pos_Main);
  if (Serial.available() > 0){
    cmd = Serial.readString();
    level = cmd[0] - '0';
    idx = cmd[1] - '0';
    Serial.println(level);
    Serial.println(idx);
    power = map(level,1,9,10,255);
    Serial.println(power);
    last_cmd_time = time_now;
    Serial.println(last_cmd_time);
    Serial.println(time_now);
   }
  //int power = map(level,1,9,10,255);
  

  if (idx == 7){
    
    if (tem > 1250 && tem < 2500){
      
      analogWrite(5,power) ;
      
    } else{
      
      analogWrite(5, 30);
      
    }
    
  } else if (idx == 8){
    
      if (tem > 1250 && tem < 2500){
        
        analogWrite(5, 30) ;
      } else {
        
        analogWrite(5,power);
        
      }
  } else if (idx == 9) {
    
    analogWrite(5,power);
    
  } else{

    analogWrite(5,0);
  }

  if ((unsigned long) (time_now - last_cmd_time) >= (unsigned long)5000){
    if (warned == false) {
      Serial.println("killed");
      warned = true;
    }
      /*Serial.println("Enter 'R' to restared");
      String restarted ;
      while (true)
      {
        analogWrite(5,0);
        if (Serial.available() > 0)
        {
          restarted = Serial.read();
          if (restarted == 'R') // This can kill the fish but cannot restarted it, need to work on it later
          {
            level = 2;
            idx = 9;
            break;
          }
        }
      }*/
      level = 0;
      idx = 0;
      
    }
    //Serial.println(last_cmd_time);
   
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
