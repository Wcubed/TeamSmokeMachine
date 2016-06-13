// Creation date: 2016-06-13
// Controlls the smoke machine, valves and the fans.

#include "constants.h"


// String to hold incoming data.
String inputString = "";
boolean newCommand = false; // True when a complete command is in the string.


void setup() {
  // Start serial communication.
  Serial.begin(9600);
  // Reserve space for the input string (to save time later).
  inputString.reserve(200);
  
  
  setup_fans();
  stop_all_fans();
}


void loop() {
  // Check if there is a command.
  if (newCommand) {
    // Just echo for now.
    Serial.print(inputString);
    
    // Clear the input string.
    inputString = "";
    newCommand = false;
  }
}



void serialEvent() {
  while (Serial.available()) {
    // Get the new byte.
    char inChar = (char)Serial.read();
    
    // Append the byte to the input string.
    inputString += inChar;
    
    // Newline means "end of command".
    // Set the flag so that the main loop can parse it.
    if (inChar == '\n') {
      newCommand = true;
    }
  }
}
