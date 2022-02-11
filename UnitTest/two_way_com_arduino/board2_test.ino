void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);//transmitter
  Serial2.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  String msg = "2";
  if(millis() % 2 == 0){
  Serial2.print(msg);}
  if(Serial1.available() > 1){//if there is more than one buffer
    String tem = Serial1.readString();
    Serial.println(tem);
  }
}
