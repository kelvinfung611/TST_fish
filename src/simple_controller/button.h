#include <ezButton.h>

ezButton button1(44);//turnVal+
ezButton button2(51);//turnVal-  
ezButton button3(45);//power+
ezButton button4(53);//power-  


void init_button() {
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); 
  button3.setDebounceTime(50); 
  button4.setDebounceTime(50); 

}

void eventListener(int & turnVal,int & power) {

  if(button1.isPressed()){
    turnVal = turnVal + 1;
    if(turnVal > 9){
      turnVal = 9;
    }
  }

  if(button2.isPressed()){
    turnVal = turnVal - 1;
    if(turnVal < 7){
      turnVal = 7;
    }
  }

  if(button3.isPressed()){
    power = power + 1;
    if(power > 9){
      power = 9;
    }
  }
  if(button4.isPressed()){
    power = power - 1;
    if(power < 0){
      power = 0;
    }
  }
}
