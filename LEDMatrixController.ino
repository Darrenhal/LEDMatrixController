#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

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

/*Adafruit_NeoPixel row0 = Adafruit_NeoPixel(NUMPIXELS, PINROW0, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row1 = Adafruit_NeoPixel(NUMPIXELS, PINROW1, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row2 = Adafruit_NeoPixel(NUMPIXELS, PINROW2, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row3 = Adafruit_NeoPixel(NUMPIXELS, PINROW3, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row4 = Adafruit_NeoPixel(NUMPIXELS, PINROW4, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row5 = Adafruit_NeoPixel(NUMPIXELS, PINROW5, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row6 = Adafruit_NeoPixel(NUMPIXELS, PINROW6, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row7 = Adafruit_NeoPixel(NUMPIXELS, PINROW7, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row8 = Adafruit_NeoPixel(NUMPIXELS, PINROW8, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row9 = Adafruit_NeoPixel(NUMPIXELS, PINROW9, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row10 = Adafruit_NeoPixel(NUMPIXELS, PINROW10, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row11 = Adafruit_NeoPixel(NUMPIXELS, PINROW11, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row12 = Adafruit_NeoPixel(NUMPIXELS, PINROW12, NEO_GRB + NEO_KHZ800);
  Adafruit_NeoPixel row13 = Adafruit_NeoPixel(NUMPIXELS, PINROW13, NEO_GRB + NEO_KHZ800);
*/

//Adafruit_NeoPixel currentStrip = Adafruit_NeoPixel(NUMPIXELS, pins[0], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel row[] = { //Initialisieren des Arrays, das die addressierbaren LED Streifen im Adafruit Format enthält
  Adafruit_NeoPixel(NUMPIXELS, PINROW0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW2, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW3, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW4, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW6, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW7, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW8, NEO_GRB + NEO_KHZ800)/*,
  Adafruit_NeoPixel(NUMPIXELS, PINROW9, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW10, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW11, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PINROW13, NEO_GRB + NEO_KHZ800)*/
};


#define DELAY 1000 //Refresh Zyklus auf 10 Millisekunden setzen
#define NUMSTRIPS 9/*(sizeof(row)/sizeof(row[0]))*/ //Anzahl der verbundenen LED Streifen definieren


int values[14][14][3];
String matrixAsString = "";

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  /*Seriellen Port über den der Pi sich mit dem Arduino verbindet einrichten*/
  Serial.begin(115200); //setzen der Bitrate auf 115200 Bit pro Sekunde
  Serial.setTimeout(100000);

  /*NeoPixel Library initialisieren*/
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].begin();
    row[i].show();
  }
}

void process(String matrixAsString) {
  DynamicJsonDocument doc(4372);
  Serial.println(matrixAsString);
  deserializeJson(doc, matrixAsString);

  Serial.println((int)(doc[2][10][0]));
  Serial.println((int)(doc[2][10][0]));
  Serial.println((int)(doc[5][10][0]));
  Serial.println((int)(doc[0][1][2]));
  Serial.println((int)(doc[0][0][1]));

  for (int i = 0; i < NUMSTRIPS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      for (int k = 0; k < 3; k++) {
        values[i][j][k] = (int)(doc[i][j][k]);
      }
    }
  }
}

void paint() {
  int r = 0;
  int g = 0;
  int b = 0;
  for (int i = 0; i < NUMSTRIPS; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      r = values[i][j][0];
      g = values[i][j][1];
      b = values[i][j][2];
      row[i].setPixelColor(j, row[i].Color(r, g, b));
      row[i].show();
    }
  }
}

//infinite loop refreshing the matrix
void loop() {

  while (Serial.available()) {
    char c = Serial.read();
    matrixAsString += c;
    if (c == '\n') {
      process(matrixAsString);
      paint();
      matrixAsString = "";
    }

  }

}
