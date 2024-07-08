#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <avr/pgmspace.h>

// benötigte Bibliothek einbinden
# include <IRremote.h>

// der Pin, an dem der Infrarot-Empfänger angeschlossen ist
#define IR_PIN 11

#define MATRIX_PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, MATRIX_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);

const uint32_t PikaDrawing[] PROGMEM = {0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xffee00 , 0xffee00 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xffee00 , 0x00edff , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000, 0x000000 , 0x000000 , 0x00acff , 0xbe3509 , 0xbe3509 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xffee00 , 0xff9b00 , 0x000000 , 0x000000 , 0x000000 ,0xff9b00 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x3da329 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x00acff , 0x00acff , 0x00acff , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xffee00 , 0xffee00 , 0xffee00 , 0xffee00 , 0xff9b00 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x3da329 , 0x3da329 , 0x3da329 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x6a552a , 0x6a552a , 0xc4ac8f , 0xc4ac8f , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xff9b00 , 0xff9b00 , 0x000000  , 0xffee00 , 0x000000 , 0xffee00 , 0xffee00 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x3da329 , 0x1abe31 , 0x3da329 , 0x1abe31 , 0x3da329 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x6a552a , 0x6a552a , 0x0091e5 , 0xc4ac8f , 0xc4ac8f , 0x0091e5 , 0x000000 , 0x000000 , 0x000000 , 0xff9b00 , 0xff9b00 , 0x000000 , 0xff0003 , 0xffee00 , 0xffee00 , 0xffee00 , 0xff9b00 , 0x000000 , 0x000000 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x3da329 , 0x1abe31 , 0x1abe31, 0x3da329 , 0x1abe31 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000, 0x6a552a , 0x6a552a , 0x8a8a8a, 0xc4ac8f , 0xc4ac8f , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xb66f00 , 0x000000  , 0xffee00 , 0xff9b00 , 0xff9b00 , 0xff9b00 , 0x000000 , 0x000000 , 0x000000 , 0xcf2600 , 0x00ff24 , 0xcf2600 , 0x00ff24 , 0x00ff24 , 0x1abe31 , 0x1abe31 , 0x3da329 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x6a552a , 0x6a552a , 0x8a8a8a, 0xc4ac8f , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xb66f00 , 0xffee00 , 0xff9b00 , 0xffee00 , 0xff9b00 , 0xffee00 , 0x000000 , 0x000000 , 0x000000 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x00ff24 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x00a2ff , 0x000000 , 0x00a2ff , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0xffee00 , 0xff9b00 , 0xb66f00 , 0xb66f00 , 0xff9b00 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x000000 , 0x00c11b , 0x00dc1f , 0x000000 , 0x00c11b , 0x00dc1f , 0x000000 , 0x000000 , 0x000000 , 0x000000
};

const uint32_t SmileyDrawing[] PROGMEM = {
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0xffee00, 0xffee00, 0xffee00, 0xffee00, 0xffee00, 0xffee00, 0x000000, 
  0xffee00, 0x000000, 0x000000, 0xffee00, 0xffee00, 0x000000, 0x000000, 0xffee00, 
  0xffee00, 0x000000, 0x00edff, 0x000000, 0x000000, 0x00edff, 0x000000, 0xffee00, 
  0xffee00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffee00, 
  0xffee00, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xffee00, 
  0x000000, 0xffee00, 0x000000, 0x000000, 0x000000, 0x000000, 0xffee00, 0x000000, 
  0x000000, 0x000000, 0xffee00, 0xffee00, 0xffee00, 0xffee00, 0x000000, 0x000000
};


uint8_t mode = 0;

void drawPika(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 32; j++) {
      int colorIndex = i * 32 + j;
      uint32_t color = pgm_read_dword(&PikaDrawing[colorIndex]);
      matrix.drawPixel(j, i, color);
    }
  }
  matrix.show();
  delay(200);
}

void drawSmiley(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int colorIndex = i * 8 + j;
      uint32_t color = pgm_read_dword(&SmileyDrawing[colorIndex]);
      matrix.drawPixel(j, i, color);
    }
  }
  matrix.show();
  delay(200);
}

int x    = matrix.width();
int pass = 0;
const uint16_t colors[] = {
  matrix.Color(255, 125, 0), matrix.Color(0, 125, 255), matrix.Color(255, 0, 0) };

void drawUwU(){
    matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("UwU"));
  if(--x < -15) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}

void drawhewwo(){
    matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("^-^ friend"));
  if(--x < -36) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(matrix.Color(127, 0, 255));

  IrReceiver.begin(IR_PIN);
}

void loop() {

  switch(mode){
    case 0:
      drawPika();
    break;
    case 1:
    drawUwU();
    break;
    case 2:
    drawhewwo();
    break;
    case 3:
    drawSmiley();
    break;
  }

  

  // decode() -> Daten lesen
  if (IrReceiver.decode())
  {
    // kurzes delay, damit nur ein Tastendruck gelesen wird
    delay(200);

    // resume -> nächsten Wert lesen
    IrReceiver.resume();

    /*
      der Empfänger empfängt zwischendurch Signale,
      die nicht ausgewertet werden können
      es sollen dehalb nur die korrekt erkannten Tasten ausgewertet werden
      die Dezimalwerte der korrekten erkannten Tasten liegen zwischen > 0 und < 95
      es wird abgefragt, ob das empfangene Kommando decodedIRData.command
      zwischen 0 und (&&) 95 liegt
    */
    if (IrReceiver.decodedIRData.command > 0 && IrReceiver.decodedIRData.command < 95)
    {
      // Werte abfragen und anzeigen
      
      if (IrReceiver.decodedIRData.command == 70) mode = 0;//Pfeil oben
      if (IrReceiver.decodedIRData.command == 68) mode = 1; // Serial.println("Pfeil links");
      if (IrReceiver.decodedIRData.command == 67) mode =2; //Serial.println("Pfeil rechts");
      if (IrReceiver.decodedIRData.command == 21) mode =3; //Serial.println("Pfeil unten");
     Serial.println(IrReceiver.decodedIRData.command); 
    }
  }
}
