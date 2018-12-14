void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 360; i++) {
   Serial.print(sin(i * (PI / 180)));
   Serial.print(" ");
   Serial.println(sin(i * (PI / 90)));
  }
}
