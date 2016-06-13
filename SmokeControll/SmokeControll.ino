// Creation date: 2016-06-13
// Controlls the smoke machine, valves and the fans.

#include "constants.h"


// String to hold incoming data.
String inputString = "";
boolean newCommand = false; // True when a complete command is in the string.


// ---- setup --------------------------------------------------------------------------

void setup() {
  // Start serial communication.
  Serial.begin(9600);
  // Reserve space for the input string (to save time later).
  inputString.reserve(200);
  
  
  setup_fans();
  stop_all_fans();
}


// ---- loop ---------------------------------------------------------------------------

void loop() {
  // Check if there is a command.
  if (newCommand) {
    // Parse the command.
    parseCommand(inputString);
    
    // Clear the input string.
    inputString = "";
    newCommand = false;
  }
}


// ---- parseCommand ---------------------------------------------------------------------------

// A typical command looks like this:
// f2i0
//
// It consists of:
// - Device (f for fan, v for valve).
// - Box number (0 -> BOXAMOUNT).
// - IN (i) or OUT (o).
// - ON (1) or OFF (0).

// Parses a command given to it.
void parseCommand(String command) {
  // Remove whitespaces and newlines.
  command.trim();
  
  // Echo the command for debugging.
  Serial.println(command);
  
  if (command.length() == 4) {
    
    char device = int(command[0]);
    byte boxNum = command[1];
    
    boolean dir = false;
    char dirChar = command[2];
    
    boolean state = int(command[3]);
    
    if (dirChar == 'i') {
      dir = IN;
    } else if (dirChar == 'f') {
      dir = OUT;
    } else {
      // ! Invalid command.
      return;
    }
    
    
    if (device == 'f') {
      Serial.println("Setting fan.");
      set_fan(boxNum, dir, state);
      
    } else if (device == 'v') {
      Serial.println("Setting valve.");
      set_valve(boxNum, dir, state);
      
    }
  }
}


// ---- serialEvent ---------------------------------------------------------------------------

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
