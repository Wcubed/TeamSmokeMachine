//High smogg values: red lights
//Low smogg values: green lights

//for the LED strips
#include "Adafruit_WS2801.h";
#include "SPI.h"; // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__;
#include <avr/power.h>;
#endif;

//initialise data and clock pins
uint8_t dataPinA  = 2;
uint8_t clockPinA = 3;

// Set the first variable to the NUMBER of pixels. 10 = 10 pixels in a row
Adafruit_WS2801 strip1 = Adafruit_WS2801(10, dataPinA, clockPinA);

void light_set(int boxNum, int boxVal int lowestVal, int highestVal) {
  boxVal = map(boxVal, lowestVal, highestVal, 0, 255);

  int R = BoxVal;
  int G = 255 - boxVal;
  int B = 0;

  uint32_t boxNum  = Color(R, G, B);
}


void light_setup(int boxNum) {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  //strip side A
  boxNum.begin();

  // Update LED contents, to start they are all 'off'
  //strip side A
  boxNum.show();
}

