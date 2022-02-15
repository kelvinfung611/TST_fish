#include <ezButton.h>

ezButton button1(50);//turnVal+
ezButton button2(51);//turnVal-  
ezButton button3(52);//power+
ezButton button4(53);//power-  


void setup() {
  Serial.begin(9600);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); 
  button3.setDebounceTime(50); 
  button4.setDebounceTime(50); 

}

void loop() {
  // need to be called first
  button1.loop(); 
  button2.loop(); 
  button3.loop(); 
  button4.loop();

  if(button1.isPressed())
    Serial.println("increase turnVal");

  if(button2.isPressed())
    Serial.println("decrease turnVal");

  if(button3.isPressed())
    Serial.println("increase power");

  if(button4.isPressed())
    Serial.println("decrease power");
}
