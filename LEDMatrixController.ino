#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*Definieren der Output-Pins für die ersten 7 LED Streifen*/
#define PINROW0 2
#define PINROW1 3
#define PINROW2 4
#define PINROW3 5
#define PINROW4 6
#define PINROW5 7
#define PINROW6 8

#define NUMPIXELS 14 //Anzahl der Pixel pro Reihe

Adafruit_NeoPixel row[] = { //Initialisieren des Arrays, das die addressierbaren LED Streifen im Adafruit Format enthält
  Adafruit_NeoPixel(NUMPIXELS, PINROW0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW6, NEO_GRB + NEO_KHZ800)
};

#define DELAY 1000 //Refresh Zyklus auf 10 Millisekunden setzen
#define NUMSTRIPS 7/*(sizeof(row)/sizeof(row[0]))*/ //Anzahl der verbundenen LED Streifen definieren

volatile int counter = 1;

void setup() {

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  /*Seriellen Port über den der Pi sich mit dem Arduino verbindet einrichten*/
  Serial.begin(115200); //setzen der Bitrate auf 115200 Bit pro Sekunde
  Serial.setTimeout(100);

  /*NeoPixel Library initialisieren*/
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].begin();
  }

}

//infinite loop refreshing the matrix
void loop() {
  /*dreidimensionales int Array einlesen
    erste Dimension enthält Adresse des adressierten LED Streifens
    zweite Dimension enthält Adresse des adressierten Pixels im Streifen
    dritte Dimension enthält RGB Wert für adressiertes Pixel
  */
  int matrix[14][14][3];
  //  matrix = Serial.read();

  int integerRead = 0;
  int i = 0;
  int j = 0;

  int c = 0;

  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].clear();
  }

  //delay(DELAY);

  row[0].setPixelColor(0, row[0].Color(255, 0, 0));
  row[1].setPixelColor(0, row[1].Color(0, 255, 0));
  row[2].setPixelColor(0, row[2].Color(0, 0, 255));
  row[3].setPixelColor(0, row[3].Color(255, 0, 255));
  row[3].setPixelColor(counter, row[3].Color(0, 255, 255));
  row[4].setPixelColor(0, row[4].Color(255, 255, 0));
  row[5].setPixelColor(0, row[5].Color(255, 0, 0));
  row[6].setPixelColor(0, row[6].Color(0, 0, 255));
  row[0].show();
  row[1].show();
  row[2].show();
  row[3].show();
  row[4].show();
  row[5].show();
  row[6].show();

  counter++;

  delay(1000);
  int c2 = 0;
  int bytesRead = 0;

if(Serial.available()) {
  matrix[5][5][1] = Serial.parseInt();
  row[5].setPixelColor(5, row[5].Color(0, matrix[5][5][1], 0));
}

/*
  while (bytesRead < 2352) {
    delay(DELAY);
    if (Serial.available()) {
      row[1].setPixelColor(8, row[1].Color(0, 255, 0));
      row[1].show();
    }
    row[6].setPixelColor(c2, row[6].Color(255, 0, 255));
    row[6].show();
    c2++;
    if (c2 >= 14) {
      row[6].clear();
      c2 = 0;
    }
    //    row[2].setPixelColor(5, row[2].Color(Serial.parseInt()
    if (Serial.available() >= 12) {
      for (int i2 = i; i2 < 14; i++) {
        for (int j2 = j; j2 < 14; i++) {
          matrix[i][j][0] = Serial.parseInt();
          matrix[i][j][1] = Serial.parseInt();
          matrix[i][j][2] = Serial.parseInt();
          bytesRead += 12;
        }
      }
    }
  }
*/
  row[3].setPixelColor(counter, row[3].Color(0, 255, 0));
  row[3].show();

  //delay(DELAY);

  /*
    while (integerRead < 588) {
      if (Serial.available() >= 12) {
        matrix[i][j][0] = Serial.parseInt();
        matrix[i][j][1] = Serial.parseInt();
        matrix[i][j][2] = Serial.parseInt();
        integerRead += 3;
        if (j < 14) {
          j++;
        } else {
          j = 0;
          i++;
        }
      }
    }
  */
  //Iterieren über alle Pixel pro Reihe und leeren dieser, um einen globalen init Zustand zu erhalten
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].clear();
  }
/*
  if (c % 2 == 0) {
    for (int i = 0; i < NUMSTRIPS; i++) {
      row[i].setPixelColor(1, row[i].Color(255, 0, 255));
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      for (int j = 0; j < NUMSTRIPS; j ++) {
        row[i].setPixelColor(j, row[i].Color(matrix[i][j][0], matrix[i][j][1], matrix[i][j][2]));
      }
    }
  }
*/
  /*Iterieren über Anzahl der Pixels pro Reihe und setzen der RGB Werte
    Danach erneutes iterieren, um die neuen Pixel-Farben anzuzeigen*/


  /*
      row[0].setPixelColor(i, row[0].Color(255, i * 5, 0));
      row[1].setPixelColor(i, row[1].Color(0, i * 5, 255));
      row[2].setPixelColor(i, row[2].Color(255, i * 5, 255));
      row[3].setPixelColor(i, row[3].Color(i * 5, i * 5, 255));
      row[4].setPixelColor(i, row[4].Color(255, i * 5, i * 5));
      row[5].setPixelColor(i, row[5].Color(0, i * 5, 0));
      row[6].setPixelColor(i, row[6].Color(0, 0, i * 5));
  */
/*
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].show();
  }
*/
  c++;
  //    delay(DELAY); //10ms warten bevor loop() erneut durchlaufen wird
}
