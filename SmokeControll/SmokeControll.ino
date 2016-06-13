// Creation date: 2016-06-13
// Controlls the smoke machine, valves and the fans.

#include "globals.h"


// String to hold incoming data.
String inputString = "";
boolean newCommand = false; // True when a complete command is in the string.

long lastMillis;


// ---- setup --------------------------------------------------------------------------

void setup() {
  // Start serial communication.
  Serial.begin(9600);
  // Reserve space for the input string (to save time later).
  inputString.reserve(200);
  
  
  setup_fans();
  setup_valves();
  
  // Close everything;
  stop_all_fans();
  close_all_valves();
}


// ---- loop ---------------------------------------------------------------------------

void loop() {
  // Calculate delta time.
  long currentMillis = millis();
  long dt = currentMillis - lastMillis;
  lastMillis = currentMillis;
  
  // Update the flow timers.
  update_flow(dt);
  
  
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

// A typical individual set command looks like this:
// sf2i0
//
// It consists of:
// - 's' for Set.
// - Device (f for fan, v for valve).
// - Box number (0 -> BOXAMOUNT).
// - IN (i) or OUT (o).
// - ON (1) or OFF (0).

// A flow command looks like this:
// f3i1000
//
// It consists of:
// - 'f' for Flow.
// - Box number (0 -> BOXAMOUNT).
// - IN (i) or OUT (o).
// - Time in milliseconds. 0 is close.


// Parses a command given to it.
void parseCommand(String command) {
  // Remove whitespaces and newlines.
  command.trim();
  
  
  if (command[0] == 'f') {
    
    // ---- Flow command -------------------------------------------------------------------------
    
    // Get the box number.
    byte boxNum = command.substring(1,2).toInt();
    
    // Get the flow direction.
    boolean dir = false;
    char dirChar = command[2];
    
    if (dirChar == 'i') {
      dir = IN;
    } else if (dirChar == 'o') {
      dir = OUT;
    } else {
      // ! Invalid command.
      return;
    }
    
    // Flow time.
    int flowTime = command.substring(3).toInt();
    
    // Start the flow.
    start_flow(boxNum, dir, flowTime);
    
  } else if (command[0] == 's') {
    
    // ---- Set command -------------------------------------------------------------------------
    
    // Get the device type.
    byte device = byte(command[1]);
    
    // Get the box number.
    byte boxNum = command.substring(2,3).toInt();
    
    boolean dir = false;
    char dirChar = command[4];
    
    boolean state = false;
    char stateChar = command[5];
    
    if (dirChar == 'i') {
      dir = IN;
    } else if (dirChar == 'o') {
      dir = OUT;
    } else {
      // ! Invalid command.
      return;
    }
    
    if (stateChar == '1') {
      state = ON;
    } else if (stateChar == '0') {
      state = OFF;
    } else {
      // ! Invalid command.
      return;
    }
    
    
    if (device == 'f') {
      
      Serial.print("Setting fan ");
      set_fan(boxNum, dir, state);
      
    } else if (device == 'v') {
      
      Serial.print("Setting valve ");
      set_valve(boxNum, dir, state);
      
    }
    
    // Debugging.
    Serial.print(boxNum);
    Serial.print(" ");
    Serial.print(dir);
    Serial.print(" to ");
    Serial.println(state);
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
