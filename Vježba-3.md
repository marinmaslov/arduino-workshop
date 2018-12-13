# Arduino
Arduino Workshop @ University of Split

## 1. Uvod: Arduino Serial Plotter
Arduino Serial Plotter je alat koji dolazi preinstaliran s Arduino IDE i koji uzima dolazne serijske podatke i prikazuje ih na plotteru.
Os y se automatski namješta vrijednostima koje se ispisuju i predstavlja vrijednost koju mjerimo (najčešće napon) pretvorenu u neki broj od 0 do 1023. 
Os x predstavlja trenutke izvršavanja naredbe: **Serial.println(vrijednost);**.
Arduino Serial Plotter se pokreće na isti način kao i Arduino Serial Monitor, a to je naredbom:  **Serial.begin(9600);**.
Vrijednost 9600 predstavlja baude. Baudi su jedinice brzine prijenosa jednake izmjene stanja signala u sekundi. Za signale sa samo dva moguća stanja jedan baud je ekvivalentan jednom bitu u sekundi.
Za otvaranje Serial Plottera: Alati/Serial Plotter

![alt text](https://static.tumblr.com/e1vmzwc/kiopjp86q/slika_1.jpg)

Za bolje razumijevanje Serial Plottera, ispišimo jedan sinusni signal na njemu:

```
void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 360; i++) {
   Serial.println(sin(i * (PI / 180)));
  }
}
```

Trebali biste dobiti slijedeće:

![alt text](https://static.tumblr.com/e1vmzwc/6Yfpjp88j/slika_2.jpg)

Serial Plotter može ispisivati više signala istovremeno, pa pokušajmo ispisati dodatnu sinusnu funkciju sa periodom upola manjim nego prethodna:

```
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
```

### Napomena:

Samo za zadnju funkciju koju ispisujemo na Serial Plotter se koristi naredba **Serial.println(vrijednost);**, za sve prije se koristi **Serial.print(vrijednost);**.

Zašto?

**print();** ispisuje nešto, ali ne uzrokuje pomak plottera (koordinatnog sustava) dok **println();** ispisuje nešto i uzrokuje pomak plottera.



## 2.	Zadatak: Fotoosjetljivi otpornik

Fotoosjetljivom otporniku se otpor smanjuje s povećanjem intenziteta ulazne svjetlosti, a otpor mu se povećava smanjenjem intenziteta ulazne svjetlosti. To svojstvo možemo iskoristiti za realizaciju sklopa koji će paliti/gasiti diodu ovisno o osvjetljenju (na isti način se pali/gasi ulična rasvjeta).

Sklop ćemo realizirati tako da ćemo u seriju s fotoosjetljivim otporom spojiti jedan otpornik od 10kΩ i diodu ćemo paliti gasiti ovisno o padu napona na tom otporu.

![alt text](https://static.tumblr.com/e1vmzwc/lgGpjp8kf/slika_3.jpg)

Iz činjenice da se za velik intenzitet svijetla otpor R1 smanjuje, prema Ohmovom zakonu će rasti pad napona na R2, a za mali ili nikakav intenzitet svijetla R1 će se povećavati, a napon na R2 će padati.

Spojite sklop prema shemi:

**Za diodu i otpornik:** digitalni port 9 (žuto) i GND (crno)

**Za otpornia i fotosjetljivi otpornik:** +5V (crveno), GND (crno), analogni port A0 (žuto)

![alt text](https://static.tumblr.com/e1vmzwc/JmDpjp8kj/slika_4.jpg)

U prvoj vježbi smo objasnili da kad pin postavimo kao INPUT da on čita stanje (napon) s elementa u krugu na kojeg je spojen, međutim tada smo bili koristili digitalni pin za čitanje stanja i ona je razlikovao samo HIGH (logička 1) i LOW (logička 0). U ovoj vježbi ćemo koristiti analogni pin jer nam treba točna vrijednost napona, a analogni za razliku od digitalnog može prepoznati bilo koju vrijednost napona.

Kod koji ćemo koristiti je slijedeći:

```
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
```

Vaš zadatak je da namjestite vrijednost u if petlji s kojom uspoređujemo naš napon (trenutno 200). Naša varijabla „vrijednost“ možda nikada ne bude ispod 200, jer kada ugasimo svijetla u prostoriji možda nam na fotoosjetljivi otpornik budu utjecala svijetla s ulice ili zaslon prijenosnog računala, stoga otvorite Serial Plotter i na temelju grafa odredite koji broj umjesto 200 bi valjalo koristiti.


## 3.	Zadatak: PIR senzor

PIR senzor (PIR: „Passive Infrared“) je senzor koji mjeri promjenu infracrvene svjetlosti unutar njegovog vidnog polja. Na taj način detektira kretnju. Sastoji se od 3 nožice: Vcc, GND i signala. Nožice su označene na pločici i vidljive su kada uklonite kapicu (kupolicu). Sadrži dva potenciometra od kojih jedan mijenja osjetljivost senzora (udaljenost do koje će senzor pratiti pokrete, do max. 7m), a drugi određuje vrijeme trajanja signala detekcije (koliko dugo će nakon detekcije senzor biti u stanju HIGH, do 5 min). Za našu vježbu nije potrebno namještati potenciometre. Također na pločici možete primijetiti i jedan „jumper“ koji je postavljen u poziciju da naš senzor odašilje HIGH stanje na detekciju pokreta i to stanje traje koliko je namješteno s potenciometrom, ali taj „jumper“ je moguće postaviti i tako da naš senzor odašilje stanje HIGH sve dok se objekt nalazi u njegovom vidnom polju, a kad se objekt pomakne iz njegovog vidnom polja stanje se promjeni u LOW.
![alt text](https://static.tumblr.com/e1vmzwc/uaWpjp8kn/slika_5.jpg)

Kako bismo najbolje pokazali kako naš PIR senzor radi detektirani pokret ćemo pokazati preko LED diode, pa spojimo sklop prema shemi (otpornik od 1kΩ):

![alt text](https://static.tumblr.com/e1vmzwc/fqDpjp8kr/slika_6.jpg)

Sada pokrenite slijedeći kod:

```
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
```

## 4.	Zadatak: Detektor laži

U ovoj vježbi ćemo napraviti jednostavan detektor laži koji će laž detektirati ovisno o promjeni otpora kože. Na ulaz sklopa spojit ćemo naše prste preko kojih ćemo mjeriti otpor. Otpor naše kože tj. cijelog ljudskog tijela mijenja se pod raznim utjecajima, a jedan od njih je i promjena raspoloženja. Tako će kada govorimo istinu otpor ostati unutar „normalnih granica“, a kada lažemo će doći do odstupanja koja ćemo kasnije izmjeriti i na temelju njih modificirati naš kod.

Shema je slijedeća:

Koristit ćemo 3 LED diode, kao indikatore stupnja laži i jedan otpornik od 2,2kΩ.

![alt text](https://static.tumblr.com/e1vmzwc/k1ppjp8kv/slika_7.jpg)

Kod je slijedeći:

```
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(4, HIGH);
  delay(500);
}

void loop()
{
  if (analogRead(A0) > 60)
  {
    digitalWrite(4, HIGH);
  }
  else
  {
    digitalWrite(4, LOW);
  }
  
  if (analogRead(A0) > 20)
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
  
  if (analogRead(A0) > 45)
  {
    digitalWrite(3, HIGH);
  }
  else
  {
    digitalWrite(3, LOW);
  }

  Serial.println(analogRead(A0));
  delay(20);
}
```

Primijetite u kodu da su unutar if petlji korištene inicijalne vrijednosti: 20, 45, 60 koje je potrebno sada namjestiti ovisno o podacima sa Serial plottera. Za početak ćemo testirati nekoga i vidjeti do kakvog odstupanja dolazi kada laže i na temelju toga ćemo odrediti nove vrijednosti za if petlje.
