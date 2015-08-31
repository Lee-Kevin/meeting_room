#include "Arduino.h"
#include "Wire.h"
#include "moudle.h"
#include <Adafruit_NeoPixel.h>
#include "matrix.h"
#include "timer.h"

MoudleClass moudle;
Adafruit_NeoPixel matrix_pixels = Adafruit_NeoPixel(256, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel timer_pixels = Adafruit_NeoPixel(40, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_pixels = Adafruit_NeoPixel(18, 4, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("hello!");
  moudle.MoudleInit();

  matrix_pixels.begin(); 
  matrix_pixels.setBrightness(20);

  timer_pixels.begin();
  timer_pixels.setBrightness(10);

  strip_pixels.begin();
  strip_pixels.setBrightness(10);

}

void loop() {
  moudle.Loop();
  Serial.println(MoudleState.PIR_State);
  if(MoudleState.PIR_State) {
      print_in_use();
      clear_all();
      setNumber(1, 1);
      setNumber(2, 0);
      timer_pixels.show();

  } else {
    print_free();
  }

  for(int i=0; i<18; i++) {
    strip_pixels.setPixelColor(i, strip_pixels.Color(0,150,0));
  }
  strip_pixels.show();

  delay(1000);

}

/* ----------Matrix--------------*/
void print_in_use(){
  for(long i=0;i<255;i++){
    matrix_pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<76;i++){
    matrix_pixels.setPixelColor(MATRIX_IN_USE[i], matrix_pixels.Color(150,0,0));
  }

  matrix_pixels.show();
}

void print_free(){
  for(long i=0;i<255;i++){
    matrix_pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<67;i++){
    matrix_pixels.setPixelColor(MATRIX_FREE[i], matrix_pixels.Color(0,150,0));
  }
  matrix_pixels.show();
}

/*-----------Timer--------------*/
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
      timer_pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, timer_pixels.Color(RED,GREEN, BLUE));
    }
  }
}

void clear_all() {
  for (int i=0; i < 40; i++){
    timer_pixels.setPixelColor(i, 0);
  }
}