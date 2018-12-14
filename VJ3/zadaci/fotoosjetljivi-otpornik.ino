int otpor = A0;
int led = 9;
int vrijednost;          

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(otpor, INPUT);
}

void loop(){
  vrijednost = analogRead(otpor);

  if (vrijednost > 200){
    digitalWrite(led, LOW);
  }
  else{
    digitalWrite(led, HIGH);
  }
  Serial.println(analogRead(A0));
  delay(2);
}
