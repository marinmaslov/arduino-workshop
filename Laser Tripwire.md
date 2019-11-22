# Arduino Laser Tripwire



[Laser Sensor Module](http://www.aliexpress.com/item/32921738771.html?spm=a2g0o.productlist.0.0.37a97dc6bK1cQc&algo_pvid=780b0c01-bf3e-4934-a67a-3937738f5a2f&algo_expid=780b0c01-bf3e-4934-a67a-3937738f5a2f-6&btsid=d66c9e6f-9026-4272-bc14-aa87beed68e0&ws_ab_test=searchweb0_0,searchweb201602_9,searchweb201603_52)
[KY-008 650nm Laser](http://www.aliexpress.com/item/32738668749.html?spm=a2g0o.productlist.0.0.37a97dc6bK1cQc&algo_pvid=780b0c01-bf3e-4934-a67a-3937738f5a2f&algo_expid=780b0c01-bf3e-4934-a67a-3937738f5a2f-0&btsid=d66c9e6f-9026-4272-bc14-aa87beed68e0&ws_ab_test=searchweb0_0,searchweb201602_9,searchweb201603_52)

[Camera](http://www.aliexpress.com/item/32969609187.html?spm=a2g0o.productlist.0.0.45353c702If6vL&algo_pvid=a419d4c2-757b-4415-a7d2-69f20f353c1a&algo_expid=a419d4c2-757b-4415-a7d2-69f20f353c1a-2&btsid=c1071830-2b17-4143-aeb1-ad68a0cbb40c&ws_ab_test=searchweb0_0,searchweb201602_9,searchweb201603_52)





## Schematics


## Code

```c++
// 5 pins trip wire

// Variables
int mode = 1;
int ambiant;
int trip = 1000; // The light value I get when using my laser
int minLight = 900;
int makeBeep = 1; //0 for no beep, 1 for beep!
int atAverage;
long millisCount;

// Output Pins
int laserPin = 2;
int ledPin = 13;
int buzzerPin = 3;
String  modeNames[3] = {"SETTINGS","ARMED","TRIP"};

// Input Pins
int modePin = 4; 
int tripPin = A0;
int ambiantPin = A1;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(modePin, INPUT);
  Serial.begin(9600);
}


void loop() {

  // When the button is pushed
  if (digitalRead(modePin) == 1) {
    trip = analogRead(tripPin);
    mode=mode + 1;
    if (mode >= 2) {
      mode = 0;
    }
    beep(1);
    delay(300);
  }

  
  //does something when the mode changes
  switch (mode) {
    case 0: //calibration mode
      digitalWrite(laserPin,HIGH);
      
      ambiant = analogRead(ambiantPin);
      trip = analogRead(tripPin);
      atAverage = ambiant + ((trip - ambiant)/2);
      stats();
      
      if (trip  >= minLight) {
        digitalWrite(ledPin,HIGH);
      } else {
        digitalWrite(ledPin,LOW);
      }

    break;

    case 1: // Armed mode
      digitalWrite(laserPin,HIGH);
      digitalWrite(ledPin,LOW);
      ambiant = analogRead(ambiantPin);
      atAverage = ambiant + ((trip - ambiant)/2);
      if (analogRead(tripPin) < atAverage) {
        mode = 2;
      }
      if ((millis() - millisCount) >= 3000) {
        millisCount = millis();
        stats();
      }
    break;
    
    case 2: //Trip Mode
      if ((millis() - millisCount) >= 1000) {
        millisCount = millis();
        stats();
        beep(3);
        mode = 1;
      }
    break;
    }

    
  delay(1);                       // wait for a bit
}

//It Beeps
void beep(int qty) {
  int count;
  if (makeBeep == 1) {
    for (count = 1;count<=qty;count++) {
      digitalWrite(buzzerPin, HIGH);
      delay(50);
      digitalWrite(buzzerPin, LOW);
      delay(50);
    }
  }
}

//Writes stats to the Serial Port
void stats() {
  Serial.print("A:");
  Serial.print(ambiant);
  Serial.print(" T:");
  Serial.print(trip);
  Serial.print(" AT:");
  Serial.print(atAverage);
  Serial.print(" MODE:");
  Serial.print(modeNames[mode]);
  Serial.println("");
}
```
