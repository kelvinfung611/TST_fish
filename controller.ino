void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

String c = "";

void loop() {
   if (Serial.available() > 0)
   {
      c = Serial.readString();
      Serial.print(c);
   }
}
