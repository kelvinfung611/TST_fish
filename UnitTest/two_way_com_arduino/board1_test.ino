void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);//transmitter
  Serial2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  String msg = "1";
  if(millis() % 2 == 0){
  Serial1.print(msg);}
  if(Serial2.available() > 1){//if there is more than one buffer
    String tem = Serial2.readString();
    Serial.println(tem);
  }
}
