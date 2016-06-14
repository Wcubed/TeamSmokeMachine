// lightControll sketch by Stijn Wolters 2016

//High smogg values: red lights
//Low smogg values: green lights

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
const int stripPin[] = { 
  3, 5, 6, 9, 10 };

// How many NeoPixels are attached to the Arduino?
const int numPixels = 10;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip;
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numPixels, stripPin[0], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numPixels, stripPin[1], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(numPixels, stripPin[2], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(numPixels, stripPin[3], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(numPixels, stripPin[4], NEO_GRB + NEO_KHZ800);

String inputString = "";         // a string to hold incoming data

int boxValues[5];

boolean newCommand;

int polutionType;

void setup() {
  strip1.begin(); // This initializes the NeoPixel library.

  Serial.begin(9600);
}

void loop() {

  // see if there's incoming serial data:
  // print the string when a newline arrives:
  if (newCommand) {
    Serial.println(inputString); 

    //seperate the input into usable information
    String header = inputString.substring(0, 1);
    int identifier = inputString.substring(1,2).toInt();
    int boxValue = inputString.substring(2).toInt();

    Serial.print("header: ");
    Serial.print(header);
    Serial.print("  ||  identifier: ");
    Serial.print(identifier);
    Serial.print("  ||  boxValue: ");
    Serial.println(boxValue);

    if(header == "T") {
      //set the color of the boxes
      Serial.print("Changing the color of the boxes to: ");
      Serial.println(identifier);
      polutionType = identifier;
      setColor();
    } 
    else if(header == "B") {
      boxValues[identifier] = boxValue;
      Serial.print("Changing the value of the box ");
      Serial.print(identifier);
      Serial.print(" to: ");
      Serial.println(boxValue);
      setColor();
    }
    // clear the string:
    inputString = "";
    newCommand = false;
  }

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      newCommand = true;
    } 
  }
}

void setColor() {
  Serial.println("Checking polution type");
  switch (polutionType) {
  case 0:
    Serial.println("Polutiontype is PM10");
    setBoxesGreen();
    break;
  case 1:
    Serial.println("Polutiontype is PM2.5");
    setBoxesRed();
    break;
  case 2:
    Serial.println("Polutiontype is N02");
    setBoxesYellow();
    break;
  case 3:
    Serial.println("Polutiontype is O3");
    setBoxesBlue();
    break;

  default: 
    // if nothing else matches, do the default
    // default is optional
    Serial.println("Polutiontype is unknown");
    setBoxesWhite();
    break;
  }
}

void setBoxesGreen() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<numPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip1.setPixelColor(i, strip1.Color(0,boxValues[0],0)); // Moderately bright green color.
    strip2.setPixelColor(i, strip2.Color(0,boxValues[1],0)); // Moderately bright green color.
    strip3.setPixelColor(i, strip3.Color(0,boxValues[2],0)); // Moderately bright green color.
    strip4.setPixelColor(i, strip4.Color(0,boxValues[3],0)); // Moderately bright green color.
    strip5.setPixelColor(i, strip5.Color(0,boxValues[4],0)); // Moderately bright green color.

  }
  strip1.show(); // This sends the updated pixel color to the hardware.
  strip2.show(); // This sends the updated pixel color to the hardware.
  strip3.show(); // This sends the updated pixel color to the hardware.
  strip4.show(); // This sends the updated pixel color to the hardware.
  strip5.show(); // This sends the updated pixel color to the hardware.
}

void setBoxesRed() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<numPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip1.setPixelColor(i, strip1.Color(boxValues[0],0,0)); // Moderately bright green color.
    strip2.setPixelColor(i, strip2.Color(boxValues[1],0,0)); // Moderately bright green color.
    strip3.setPixelColor(i, strip3.Color(boxValues[2],0,0)); // Moderately bright green color.
    strip4.setPixelColor(i, strip4.Color(boxValues[3],0,0)); // Moderately bright green color.
    strip5.setPixelColor(i, strip5.Color(boxValues[4],0,0)); // Moderately bright green color.

  }
  strip1.show(); // This sends the updated pixel color to the hardware.
  strip2.show(); // This sends the updated pixel color to the hardware.
  strip3.show(); // This sends the updated pixel color to the hardware.
  strip4.show(); // This sends the updated pixel color to the hardware.
  strip5.show(); // This sends the updated pixel color to the hardware.
}

void setBoxesYellow() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<numPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip1.setPixelColor(i, strip1.Color(boxValues[0],boxValues[0],0)); // Moderately bright green color.
    strip2.setPixelColor(i, strip2.Color(boxValues[1],boxValues[1],0)); // Moderately bright green color.
    strip3.setPixelColor(i, strip3.Color(boxValues[2],boxValues[2],0)); // Moderately bright green color.
    strip4.setPixelColor(i, strip4.Color(boxValues[3],boxValues[3],0)); // Moderately bright green color.
    strip5.setPixelColor(i, strip5.Color(boxValues[4],boxValues[4],0)); // Moderately bright green color.

  }
  strip1.show(); // This sends the updated pixel color to the hardware.
  strip2.show(); // This sends the updated pixel color to the hardware.
  strip3.show(); // This sends the updated pixel color to the hardware.
  strip4.show(); // This sends the updated pixel color to the hardware.
  strip5.show(); // This sends the updated pixel color to the hardware.
}

void setBoxesBlue() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<numPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip1.setPixelColor(i, strip1.Color(0,0,boxValues[0])); // Moderately bright green color.
    strip2.setPixelColor(i, strip2.Color(0,0,boxValues[1])); // Moderately bright green color.
    strip3.setPixelColor(i, strip3.Color(0,0,boxValues[2])); // Moderately bright green color.
    strip4.setPixelColor(i, strip4.Color(0,0,boxValues[3])); // Moderately bright green color.
    strip5.setPixelColor(i, strip5.Color(0,0,boxValues[4])); // Moderately bright green color.

  }
  strip1.show(); // This sends the updated pixel color to the hardware.
  strip2.show(); // This sends the updated pixel color to the hardware.
  strip3.show(); // This sends the updated pixel color to the hardware.
  strip4.show(); // This sends the updated pixel color to the hardware.
  strip5.show(); // This sends the updated pixel color to the hardware.
}

void setBoxesWhite() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<numPixels;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip1.setPixelColor(i, strip1.Color(boxValues[0],boxValues[0],boxValues[0])); // Moderately bright green color.
    strip2.setPixelColor(i, strip2.Color(boxValues[1],boxValues[1],boxValues[1])); // Moderately bright green color.
    strip3.setPixelColor(i, strip3.Color(boxValues[2],boxValues[2],boxValues[2])); // Moderately bright green color.
    strip4.setPixelColor(i, strip4.Color(boxValues[3],boxValues[3],boxValues[3])); // Moderately bright green color.
    strip5.setPixelColor(i, strip5.Color(boxValues[4],boxValues[4],boxValues[4])); // Moderately bright green color.

  }
  strip1.show(); // This sends the updated pixel color to the hardware.
  strip2.show(); // This sends the updated pixel color to the hardware.
  strip3.show(); // This sends the updated pixel color to the hardware.
  strip4.show(); // This sends the updated pixel color to the hardware.
  strip5.show(); // This sends the updated pixel color to the hardware.
}



