#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//definieren der Pinbelegung
#define PINROW0 2
#define PINROW1 3
#define PINROW2 4
#define PINROW3 5
#define PINROW4 6
#define PINROW5 7
#define PINROW6 8
#define PINROW7 22
#define PINROW8 24
#define PINROW9 26
#define PINROW10 28
#define PINROW11 30
#define PINROW12 32
#define PINROW13 34

#define NUMPIXELS 14 //Anzahl der Pixel pro Reihe

Adafruit_NeoPixel row[] = { //Initialisieren des Arrays, das die addressierbaren LED Streifen im Adafruit Format enthält
  Adafruit_NeoPixel(NUMPIXELS, PINROW0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW6, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW7, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW8, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW9, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW10, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW11, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW13, NEO_GRB + NEO_KHZ800)
};


#define DELAY 1000 //Refresh Zyklus auf 10 Millisekunden setzen
#define NUMSTRIPS 14 //Anzahl der verbundenen LED Streifen definieren


uint8_t values[NUMSTRIPS][NUMPIXELS][3]; //lokale Repräsentation der RGB Werte aller LEDs als Matrix als unsigned 8 Bit int
int input[588]; //Array zum Halten der eingelesenen Daten (eine komplette Matrix entspricht 14*14*3 Werten --> Array-Länge 588)
int c = 0; //Counter-Variable zum Zuweisen der eingelesenen Werte in das input-Array
int r = 0; //Counter-Variable zum Auslesen der Werte aus dem input-Array
uint8_t in = 0; //Variable, die den gerade eingelesenen unsigned int hält
void setup() { //Einstellungen, die zu Beginn der Anwendung/sobald eine serielle Verbindung aufgebaut wird eingestellt werden

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  /*Seriellen Port über den der Pi sich mit dem Arduino verbindet einrichten*/
  Serial.begin(115200); //setzen der Bitrate auf 115200 Bit pro Sekunde
  Serial.setTimeout(100000); //Port-Timeout auf 100s setzen

  /*NeoPixel Library initialisieren*/
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].begin(); //LED Streifen initialisieren
    row[i].show(); //initialisierten Zustand anzeigen
  }
}

void process() {
  for (int i = 0; i < NUMSTRIPS; i++) { //iterieren über int[14][14][3]-Array mit 3 Schleifen (1 Schleife je Dimension)
    for (int j = 0; j < NUMPIXELS; j++) {
      for (int k = 0; k < 3; k++) {
        values[i][j][k] = input[r]; //Ein Wert nach dem anderen aus den eingelesen Daten auslesen und in jeweils nächstem RGB Wert speichern
        r++; //Hochzählen der Variable, mit welcher auf die eingelesenen Daten zugegriffen wird
      }
    }
  }
  r = 0; //Zurücksetzen der Lesezugriffsvariable
}

void paint() {
  int r = 0; //RGB Werte auf 0 setzen
  int g = 0;
  int b = 0;
  for (uint8_t i = 0; i < NUMSTRIPS; i++) { //iterieren über int[14][14][3]-Array mit 2 Schleifen (je 1 für x- und y-Koordinaten
    for (uint8_t j = 0; j < NUMPIXELS; j++) {
      r = values[i][j][0]; //Auslesen der RGB Werte an der entsprechenden Stelle
      g = values[i][j][1];
      b = values[i][j][2];
      row[i].setPixelColor(j, row[i].Color(r, g, b)); //RGB Werte für entsprechenden LED Streifen (i / x-Koordinate) an der entsprechenden Stelle (j / y-Koordinate) setzen
    }
    row[i].show(); //LED Streifen anzeigen
  }
}

//Endlos-Schleife; wird automatisch am Ende von setup() gerufen
void loop() {

  while (Serial.available()) { //Schleife durchlaufen, solange Daten an der seriellen Schnittstelle anliegen
    in = Serial.read(); //Einlesen des vordersten Bytes der Daten, die an der seriellen Schnittstelle anliegen
    if (in < 0) { //RGB Wert kann maximal 255 sein --> = max Wert bei unsigned int, bei signed int max Wert nur 127 --> 255 unsigned = -1 signed --> überprüfen, ob signed int vorliegt
      input[c] = in + 256; //falls signed int --> umrechnen auf unsigned int durch addieren von 256 und speichern in größerem Datentyp, der mehr als 256 Werte darstellen kann
    } else {
      input[c] = in; //ansonsten direkt in größerem Datentyp speichern
    }
    if (c < 587) { //Solange nicht alle Daten (588 int Werte) eingelesen sind -->
      c++; //Variable zum Zählen der Anzahl eingelesener Bytes hochzählen
    } else {
      c = 0; //Sobald alle Daten eingelesen sind --> Variable wieder auf 0 setzen
      process(); //Daten verarbeiten und in richtiges Format mappen
      paint(); //LEDs ansteuern
    }
  }

}
