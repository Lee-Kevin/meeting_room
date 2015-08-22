#include "Arduino.h"
#include "Wire.h"
#include "moudle.h"
#include <Adafruit_NeoPixel.h>
#include "matrix.h"

MoudleClass moudle;
Adafruit_NeoPixel matrix_pixels = Adafruit_NeoPixel(256, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("hello!");
  moudle.MoudleInit();

  matrix_pixels.begin(); 
  matrix_pixels.setBrightness(10);


}

void loop() {
  moudle.Loop();
  Serial.println(MoudleState.PIR_State);
  if(MoudleState.PIR_State) {
      print_in_use();
      

  } else {
    print_free();
  }


  delay(1000);

}

/* ----------Matrix--------------*/
void print_in_use(){
  for(long i=0;i<255;i++){
    matrix_pixels.setPixelColor(i, 0);
  }
  for(long i=0;i<78;i++){
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