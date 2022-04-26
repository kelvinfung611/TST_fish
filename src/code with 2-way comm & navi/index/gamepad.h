void eventListener(int & xMap, int & yMap, int & turnVal,int & power) {
  // need to be called first
  char cmd [4];
  char input;
  int input_num;
  if(Serial2.available() > 0){
    //read until the start
    input = Serial2.read(); //*
    while(input != '*'){
      input = Serial2.read();
      }
     input_num = Serial2.parseInt();//1234
     Serial2.read(); //!
     xMap = (input_num/1000U) % 10;
     yMap = (input_num/100U) % 10;
     turnVal = (input_num/10U) % 10;
     power = (input_num/1U) % 10;
}
}
