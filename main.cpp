#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// 1 is forward, -1 is reverse
int direction = 1;

int col = 0;

int i = 0;

uint8_t c;

Adafruit_NeoPixel matrix = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// Accepts 0 - 36 index
int sine_map[] =
{ 128 , 150 , 171 , 191 , 209 , 225 ,
  238 , 247 , 253 , 255 , 253 , 247 ,
  238 , 225 , 209 , 191 , 171 , 150 ,
  128 , 105 , 84 , 64 , 46 , 30 ,
  17 , 8 , 2 , 0 , 2 , 8 ,
  17 , 30 , 46 , 64 , 84 , 105 ,
  127
};


void setup() {
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'
}

void color_row(int col_index, int r, int g, int b) {
  matrix.setPixelColor(0 + col_index, r, g, b);
  matrix.setPixelColor(8 + col_index, r, g, b);
  matrix.setPixelColor(16 + col_index, r, g, b);
  matrix.setPixelColor(24 + col_index, r, g, b);
  matrix.setPixelColor(32 + col_index, r, g, b);
  matrix.show();
}

// get the remainder of micros over 2000
// iterate over 0 -> 7 columns
  // multiply index by 45: position in 360 degree space
  // map zero -> remainder -> 2000 into 0 -> value -> 360 space
  // add up and integer divide by two
  // get the sine estimation of that degree value
  // use that sine value RBG to color_row
  // call color_row with the index, and the value for all three
void color_sine(int elapsed_millis) {
  for (int i = 0; i < 8; i++) {
    int cycle = elapsed_millis % 2000;
    int time_degrees = map(cycle, 0, 2000, 0, 360); 
    int pos_degrees = i * 45;
    int degrees = (time_degrees + pos_degrees) / 2;
    int sine_index = degrees / 10;
    int color_value = sine_map[sine_index];
    c = color_value / 10;
    color_row(i, c, c, c);
  }
  matrix.show();
}

void loop() {
  color_sine(millis());
}



