int pir = 3;
int led = 2;

void setup() {
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);  
  Serial.begin(9600);        
}

void loop() {
  int val = digitalRead(pir);
  digitalWrite(led, val);
  Serial.println(val);
  if (val == 1) {
    digitalWrite(led, HIGH);
  }
}
