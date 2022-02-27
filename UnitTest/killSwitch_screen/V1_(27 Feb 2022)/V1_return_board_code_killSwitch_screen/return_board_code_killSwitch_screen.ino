void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);

}

char incoming;
String cmd[12];
bool check;
int ascii_sum;
int turn = 0;

bool checkSum(char coming, int x, char command[]){
  check = false;
  int cSum = 0;
  for (int i = 0; i < 8; i++){
    cSum += command[i];
  }
  String numcheck = String(command[8]) + String(command[9]) +String(command[10]);
  int number = numcheck.toInt();
  if (cSum == number)
  {
    check = true;
  }
  return check;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    while (incoming != '?'){
      incoming = Serial.read();
    }
    char cmd[12];
    int i = -1;
    while (i < 12 and incoming != '/'){
      if (Serial.available() > 0){
        cmd[i] = incoming;
        i++;
        incoming = Serial.read();
      }
    }
    if (Serial.available() > 60){
      while (Serial.available() > 0){
        Serial.read();
      }
    }
    //cmd[11] = '/0';
    //Serial.println(cmd);
    check = checkSum(incoming, i, cmd );
    
    //bool checkd = false;
    if (check == true && turn % 2 == 0){
      ascii_sum = 'S' + '8' + 'V' + '1' + '2' + '3' + 'C' + '4' + '5' + '6' + 'R' + '3' + '2' + '1' + '0';
      if (ascii_sum < 1000){
        Serial.println((String) "!S8V123C456R3210" + "0" + ascii_sum + "$");
      } else{
        Serial.println((String) "!S8V123C456R3210" + ascii_sum + "$");
      }
      turn = turn + 1;
     
    } else if (check == true && turn % 2 == 1){
      
      ascii_sum = 'S' + '4' + 'V' + '3' + '9' + '5' + 'C' + '4' + '1' + '0' + 'R' + '3' + '2' + '6' + '8';
      if (ascii_sum < 1000) {
        Serial.println((String) "!S4V395C410R3268" + "0" + ascii_sum + "$");
      } else{
        Serial.println((String) "!S4V395C410R3268" + ascii_sum + "$");
      }
      turn = turn + 1;
    }
    
  }

  
}
