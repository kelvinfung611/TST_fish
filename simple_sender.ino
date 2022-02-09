void setup() {
  Serial.begin(9600);
}

String c = "";

void loop() {
   if (Serial.available() > 0)
   {
      c = Serial.readString();
      Serial.print(c);
   }
}
