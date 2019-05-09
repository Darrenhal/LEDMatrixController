#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/*Definieren der Output-Pins für die ersten 7 LED Streifen*/
#define PINROW 0
#define PINROW 1
#define PINROW 2
#define PINROW 3
#define PINROW 4
#define PINROW 5
#define PINROW 6

#define NUMPIXELS 14 //Anzahl der Pixel pro Reihe

Adafruit_NeoPixel row[] = { //Initialisieren des Arrays, das die addressierbaren LED Streifen im Adafruit Format enthält
  Adafruit_NeoPixel(NUMPIXELS, PINROW0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW5, NEO_GRB + NEO_KHZ800)
};

#define DELAY 10; //Refresh Zyklus auf 10 Millisekunden setzen
#define NUMSTRIPS 7/*(sizeof(row)/sizeof(row[0]))*/ //Anzahl der verbundenen LED Streifen definieren

void setup() {

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

/*Seriellen Port über den der Pi sich mit dem Arduino verbindet einrichten*/
  Serial.begin(9600);
  Serial.setTimeout(50);

/*NeoPixel Library initialisieren*/
  pixels.begin();
}

//infinite loop refreshing the matrix
void loop() {
  /*dreidimensionales int Array einlesen
  erste Dimension enthält Adresse des adressierten LED Streifens
  zweite Dimension enthält Adresse des adressierten Pixels im Streifen
  dritte Dimension enthält RGB Wert für adressiertes Pixel
  */
  int[][][] = Serial.readInt[][][]();

  //Iterieren über alle Pixel pro Reihe und leeren dieser, um einen globalen init Zustand zu erhalten
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].clear();
  }

  /*Iterieren über Anzahl der Pixels pro Reihe und setzen der RGB Werte
  Danach erneutes iterieren, um die neuen Pixel-Farben anzuzeigen*/
  for(int i=0;i<NUMPIXELS;i++){

    row[0].setPixelColor(i, row[0].Color(255, i*5, 0));
    row[1].setPixelColor(i, row[1].Color(0, i*5, 255));
    row[2].setPixelColor(i, row[2].Color(255, i*5, 255));
    row[3].setPixelColor(i, row[3].Color(i*5, i*5, 255));
    row[4].setPixelColor(i, row[4].Color(255, i*5, i*5));
    row[5].setPixelColor(i, row[5].Color(0, i*5, 0));
    row[6].setPixelColor(i, row[6].Color(0, 0, i*5));

    for(int i = 0; i < NUMSTRIPS; i++) {
      row[i].show();
    }

    delay(DELAY); //10ms warten bevor loop() erneut durchlaufen wird
}
