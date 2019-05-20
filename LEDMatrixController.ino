#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

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


int values[7][14][3];
int c = 0;
String matrixAsString = "";

void setup() {

  /*Seriellen Port über den der Pi sich mit dem Arduino verbindet einrichten*/
  Serial.begin(115200); //setzen der Bitrate auf 115200 Bit pro Sekunde
  Serial.setTimeout(1000);

  for (int i = 0; i < 7; i++) {
    for (int j = 0; i < 14; j++) {
      values[i][j][0] = values[i][j][1] = values[i][j][2] = 0;
    }
  }

  /*NeoPixel Library initialisieren*/
  for (int i = 0; i < NUMSTRIPS; i++) {
    row[i].begin();
  }
}

void process(String matrixAsString) {
  StaticJsonDocument<2186> doc;
  deserializeJson(doc, matrixAsString);

  for (int i = 0; i < 7; i++) {
    for (int j = 0; i < 14; j++) {
      values[i][j][0] = values[i][j][1] = values[i][j][2] = (int) (doc[i][j][0]);
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
      matrixAsString = "";
    }

  }

}
