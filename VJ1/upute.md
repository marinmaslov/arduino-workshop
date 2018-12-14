# Arduino Vježba 3
Arduino Workshop @ University of Split

## 1.	Instalacija Arduina
Potrebno je instalirati program Arduino IDE i drivere za Arduino pločice.

Instalacijske pakete možete pronaći na: https://mega.nz/#F!1lFShAQa
Arduino i driveri se instaliraju na isti način kao i svaki drugi program.

### Prvo postavljanje Arduina
Pokrenite program.

Kako bismo ispravno koristili Arduino kompajler s našom pločicom idite na Tools pa na Bord i odaberite: Arduino Duemilanove or Diecimila

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_01.jpg)

Zatim idite na Tools pa na Processor i odaberite: ATmega328P

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_02.jpg)

## 2.	Osnove Arduino programiranja (pomoću LED dioda)
Kada otvorite vaš Arduino compiler pojavit će vam se slijedeće:

```
void setup() {
U „void setup()“ upisujemo kod koji će se izvršavati samo jednom.
}
void loop() {
U „void loop()“ upisujemo kod koji će se izvršavati beskonačno puta.
}
```

### Postavljanje pinova

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_03.jpg)

Radimo sa mikrokontrolerom CROduino Basic2. On sadrži pinove naznačene na slici. U inicijalnom stanju svi su pino isključeni, kako bismo ih uključili koristimo naredbu: **int ime_koje_mi_dodjeljujemo = broj_pina;**. Ove linije koda pišu se na početku samog programa, dakle izvan petlji **setup()** i **loop()**.

### Zadatak 1
Npr. Ako želimo uključiti digitalni pin 1 pišemo: 

```
int pin = 1;
void setup() {
}
void loop() {
}
```

Kako bismo najlakše objasnili kako se pinovi pale koristit ćemo LED diode.

Spojite crvenu diodu na digitalni pin 3 prema slici:

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_04.jpg)

Zatim u Arduino compiler upišite slijedeći kod:

```
int led = 3;
void setup() {
	pinMode(led, OUTPUT);
}
void loop() {
digitalWrite(led, HIGH);
}
```

O naredbama:
### pinMode(led, OUTPUT);
Naredbama postavlja pin u OUTPUT ili INPUT mode, OUTPUT mode znači da će pin davati neki izlaz, INPUT mode znači da će pin primati neki ulaz.

### digitalWrite(led, HIGH);
Ako je pin postavljen kao OUTPUT, možemo konfigurirati njegov izlaz, kako koristimo digitalne pinove izlaz mu može biti ili logička jedinica (HIGH) ili logička nula (LOW).


### Zadatak 2
Pokušajmo sada namjestit da se naša led dioda pali i gasi.
Potrebno je dodati slijedeći kod:

```
int led = 3;
void setup() {
	pinMode(led, OUTPUT);
}
void loop() {
digitalWrite(led, HIGH);
delay(100);
digitalWrite(led, LOW);
delay(100);
}
```

O naredbama:
### digitalWrite(led, HIGH);
Postavlja pin u logičku jedinicu.

### delay(100);
Kada kompajler dođe do linije koda s ovom naredbom pročita vrijednost iz zagrade u milisekundama i toliko čeka prije nastavka izvršavanja koda.

### digitalWrite(led, LOW);
Postavlja pin u logičku nulu.

Kako nam se **digitalWrite()** i  **delay()** funkcije izvršavaju u **loop()** – beskonačnoj petlji LED dioda će se paliti i gasiti dok god postoji napajanje.

### Zadatak 3
Pokušajmo sada dodati „fade“ efekt našoj diodi, tj. ne želimo da samo treperi već ćemo pokušati namjestiti da se postepeno isjenčava iz logičke 1 u logičku 0.
Rekli biste da je to nemoguće jer koristimo digitalne pinove i oni imaju fiksne vrijednosti napona za logičku jedinicu i nulu. Ali postoje PWM (Pulse-width modulation) digitalni pinovi, pomoću kojih je modulacijom našeg digitalnog signala moguće postići „fade“ efekt. Koji pinovi su PWM možete vidjeti na slici s Croduino Pinout-om.

Pa krenimo, trebamo napisati slijedeći kod:

````
int led = 3;
int brightness = 0;
int fadeAmount = 5;
void setup() {
	pinMode(led, OUTPUT);
}
void loop() {
analogWrite(led, brightness);
brightness = brightness + fadeAmount;
if (brightness <= 0 || brightness >= 255) {
fadeAmount = -fadeAmount;
} 
delay(30);
}
````

Objasnimo kod:

Na početku inicijaliziramo 2 varijable: brightness i fadeAmount, koje ćemo koristiti za stvaranje našeg „fade“ efekta. Zatim nakon što program naš pin postavi u **OUTPUT** u petlji **setup()**, ulazimo u **loop()** petlju u kojoj ne postavljamo pin na **HIGH** već na vrijednost brightness koja kreće od 0 (logičke 0). Svakom iteracijom beskonačne petlje se vrijednost brightness-a povećava za vrijednost fadeAmount-a (ledica se postepeno pali do maksimuma), sve do trenutka u kojem brightness ne bude veći ili jednak 255 (maksimum), tada negiramo vrijednost fadeAmount, te će se ledica istom logikom početi postepeno gasiti (smanjuje se brightness za vrijednost fadeAmount-a) dok brightness ne dođe na vrijednost 0, i tako u krug.

### Zadatak 4 (samostalan)
Pokušajte spojiti 4 LED diode, svaku na svoj pin i napisati program koji će ih nasumično paliti (funkcija **random();**).

````
int n = random(p, q);
// n će nasumično generirati brojeve u rasponu od p do q-1 
````

## 3.	Ultrazvučni senzor
### Shema
Spojite senzor prema shemi:

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_05.jpg)

### Zadatak 1
Senzor je uspješno spojen, ali trenutno ništa ne radi jer mu nismo napisali program. Prije nego napišemo program sjetimo se par osnova fizike:

Brzina zvuka: v_z=340 m/s

Pretvoreno u cm/(µs) iznosi: v_z=0,034  cm/(µs)

Brzina: v=s/t

Iz brzine izrazimo vrijeme: t=s/v

Za udaljenost od 10cm zvuku treba: t=(10 cm)/(0,034 cm/(µs))=294 µs

Senzor će nam umjesto 294 µs vraćati 2∙294,tj.vrijeme potrebno za zvučni val da stigne do objekta zbrojeno s vremenom potrebnim da se zvučni val reflektira i vrati do senzora

Dakle konačnu udaljenost ćemo računati kao:
s_k=t∙v/2=(t∙0,034)/2  [cm]

Program:

Kako bismo uspješno mjerili udaljenost, trebamo postaviti trigPin, u našem slučaju je to pin 9, u stanje HIGH stanje na 10µs, s time da je taj pin postavljen kao OUTPUT. Nakon što se trigPin postavi u HIGH stanje, senzor generira se 8 ultrazvučnih impulsa. Ti impulsi se reflektiraju o objekt dok kojeg mjerimo udaljenost, a njihov prijem se odvija preko echoPin-a. Dakle, echoPin, u našem slučaju pin 10, postavljamo kao INPUT. Nakon toga ćemo poslati naš val čiju ćemo refleksiju primiti i izračunati udaljenost.

````
// definirajmo pinove koje koristimo kao konstante (9 i 10)
const int trigPin = 9;
const int echoPin = 10;

// definirajmo naše varijable vrijeme (vrijednost koju nam daje senzor) i udaljenost (koju računamo pomoću vremena)
long vrijeme;
double udaljenost;

void setup() {
// Postavljamo pin 9 (trig) kao Output
pinMode(trigPin, OUTPUT);
// Postavljamo pin 10 (echo) kao Input
pinMode(echoPin, INPUT); 
// Započnimo serijsku komunikaciju kako bi mogli pratiti rezultate na našem monitoru (Tools/Serial Monitor)
Serial.begin(9600); 
}

void loop() {
// Za početak želim postaviti trigPin u LOW, ovo radimo kao sigurnosnu mjeru ako je taj pin ostao u stanju HIGH pa ne bismo znali kad je započeo naš interval od 10µs, tj. možda bi taj interval trajao i dulje
// Zatim koristimo funkciju delayMicroseconds() kako bi nam se izvršavanje programa zaustavilo na 2µs
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Za generiranje ultrazvučnih impulsa postavljamo trigPin u HIGH i koristimo delayMicroseconds() kako bi stao u stanju HIGH prije nego ga postavimo u LOW
// Ovdje generiramo naših 8 impulsa u trajanju od 10µs
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Sada ćemo pročitati koliko je vremena trebalo da se val reflektira i vrati natrag senzoru
// Reflektirani val se vraća natrag na echoPin isto u obliku impulsa koji su u HIGH stanju
// Te povratne impulse čitamo pomoću funkcije pulseIn(), ona ne mora nužno čitati HIGH impulse može i LOW, sve ovisi o logici kojom želimo realizirati sklop
vrijeme = pulseIn(echoPin, HIGH);

// U ovoj liniji računamo udaljenost prema formuli, udaljenost se izražava u cm
udaljenost = (vrijeme*0.034/2);


// Ispisujemo rezultat na Serial Monitoru print() se koristi za ispis teksta, a printIn() za ispis varijabli
Serial.print("Udaljenost: ");
Serial.println(udaljenost);
}
````

### Zadatak 2
Pokušajmo sada napraviti led indikator udaljenosti, npr. spojimo 5 LED dioda i svaka indicira udaljenost od 10cm. Dakle, kada svijetli 1 objekt je od senzora udaljen 10cm, kada svijetle 2, udaljen je 20cm, itd.
Spojite elemente prema slijedećoj shemi:

![alt text](https://raw.githubusercontent.com/marinmaslov/Arduino/master/VJ1/slike/slika_06.jpg)

Sada napišimo program koji će paliti LED diode ovisno o udaljenosti:

````
const int trigPin = 9;
const int echoPin = 10;
// inicijalizirajmo naše LED diode
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
long vrijeme;
double udaljenost;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  // Postavimo LED diode kao OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  vrijeme = pulseIn(echoPin, HIGH);
  udaljenost = (vrijeme*0.034/2);
  // Ovaj dio koda pali/gasi ledice po potrebi
  if(udaljenost<=10) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if(udaljenost<=20 && udaljenost>=10) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if(udaljenost<=30 && udaljenost>=20) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else if(udaljenost<=40 && udaljenost>=30) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
  }
  else {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  Serial.print("Udaljenost: ");
  Serial.println(udaljenost);
}
````
