#include <Adafruit_NeoPixel.h>
#include "timer.h"

#define PIN            7

#define NUMPIXELS      82

#define RED 0
#define GREEN 255
#define BLUE 255

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);
  Serial.println("Hello!");

  pixels.begin(); 
  pixels.setBrightness(10);
}

void loop() {

  for(int i=0; i<10; i++) {
    clear_all();
    setNumber(1, i);
    setNumber(2, i);
    pixels.show();
    delay(1000);
  }


}

void setNumber(int index, int num) {
  if (index < 1 || index > 2)
    return;
  if (num < 0 || num > 9)
    return;

  int mbreak;
  mbreak = false;

  for (int i=0;i<7;i++) {
    if(mbreak)
      break;
    if (NUMBER[num][i] == 6)
      mbreak = true;
    Serial.println();
    for(int j=0; j<EVERY_PIXEL; j++) {
      int stroke_number = NUMBER[num][i];
      pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, pixels.Color(RED,GREEN, BLUE));
    }
  }
}

void clear_all() {
  for (int i=0; i < 40; i++){
    pixels.setPixelColor(i, 0);
  }
}
