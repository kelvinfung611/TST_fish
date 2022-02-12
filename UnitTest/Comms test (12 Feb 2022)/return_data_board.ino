void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

char incoming;
String cmd[12];
bool check;
int ascii_sum;

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
    Serial.println(cmd);
    check = checkSum(incoming, i, cmd );
    
    //bool checkd = false;
    if (check == true){
      ascii_sum = 'S' + '8' + 'V' + '1' + '2' + '3' + 'C' + '4' + '5' + '6' + 'R' + '3' + '2' + '1' + '0';
      if (ascii_sum < 1000){
        Serial.println((String) "!S8V123C456R3210" + "0" + ascii_sum + "$");
      } else{
        Serial.println((String) "!S8V123C456R3210" + ascii_sum + "$");
      }
     
    } else {
      
      ascii_sum = 'S' + 'x' + 'V' + 'x' + 'x' + 'x' + 'C' + 'x' + 'x' + 'x' + 'R' + 'x' + 'x' + 'x' + 'x';
      if (ascii_sum < 1000) {
        Serial.println((String) "!SxVxxxCxxxRxxx" + "0" + ascii_sum + "$");
      } else{
        Serial.println((String) "!SxVxxxCxxxRxxx" + ascii_sum + "$");
      }
    }
  }
}
