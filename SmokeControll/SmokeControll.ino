// Controlls the smoke machine, valves and the fans.
// Author: Stijn Wolters, Wybe Westra
// Creation date: 2016-06-13

#include "globals.h"


//#define DEBUG;


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
  
  setup_state();
  
  setup_servos();
  
  // Close everything;
  stop_all_fans();
  close_all_valves();
  
  lastMillis = millis(); // Start the timer.
}


// ---- loop ---------------------------------------------------------------------------

void loop() {
  // Calculate delta time.
  long currentMillis = millis();
  long dt = currentMillis - lastMillis;
  lastMillis = currentMillis;
  
  // Update the flow timers.
  update_flow(dt);
  
  // Update the program state.
  update_state(dt);
  
  // Update the servo timers.
  update_servos(dt);
  
  
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

// Individual Set
// Sets a fan or valve to a particular state.
//
// A typical individual set command looks like this:
// sf2i0
//
// It consists of:
// - 's' for Set.
// - Device (f for fan, v for valve).
// - Box number (0 -> BOXAMOUNT).
// - IN (i) or OUT (o).
// - ON (1) or OFF (0).

// ---- Flow level --------------------------------------------------------------------------

// Set Timed Flow
// Starts an input or output flow that lasts a cretain time.
//
// A flow command looks like this:
// f3i1000
//
// It consists of:
// - 'f' for Flow.
// - Box number (0 -> BOXAMOUNT).
// - IN (i) or OUT (o).
// - Time in milliseconds. 0 is close.

// Clear All
// Runs all the output flows for a certain amount of time.
//
// The clear all command is just one letter:
// c
// For the default clear time.
//
// Or with a number after it:
// c3000
// Where the number is the time in milliseconds.

// ---- High level commands ----------------------------------------------------------------------

// Set Pollution type
//
// t0
//
// - 't' for Type.
// - Pollution type ID (0 -> 4)

// Set Box Target Value
//
// b350
//
// - 'b' for Box.
// - Box number (0 -> BOXAMOUNT).
// - The rest is the smoke target value.

// Execute Orders.
// Executes currently stored box value orders.
//
// g
//
// - 'g' for Go.


// Parses a command given to it.
void parseCommand(String command) {
  // Remove whitespaces and newlines.
  command.trim();
  
  
  if (command[0] == 'f') {
    
    // ---- Timed Flow  -------------------------------------------------------------------------
    
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
    long flowTime = command.substring(3).toInt();
    
    if (boxNum >= 0 && boxNum < BOXAMOUNT) {
      // Start the flow.
      start_flow(boxNum, dir, flowTime);
    }
    
    #ifdef DEBUG;
      Serial.print("Setting ");
      Serial.print(dir);
      Serial.print(" flow of box ");
      Serial.print(boxNum);
      Serial.print(" to ");
      Serial.println(flowTime);
    #endif;
    
  } else if (command[0] == 's') {
    
    // ---- Individual Set  -------------------------------------------------------------------------
    
    // Get the device type.
    char device = byte(command[1]);
    
    // Get the box number.
    byte boxNum = command.substring(2,3).toInt();
    
    boolean dir = false;
    char dirChar = command[3];
    
    boolean state = false;
    char stateChar = command[4];
    
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
    
    
    if (boxNum >= 0 && boxNum < BOXAMOUNT+1) {
      if (device == 'f') {
        
        #ifdef DEBUG;
          Serial.print("Setting fan ");
        #endif;
        
        set_fan(boxNum, dir, state);
        
      } else if (device == 'v') {
        
        #ifdef DEBUG;
          Serial.print("Setting valve ");
        #endif;
        
        set_valve(boxNum, dir, state);
        
      }
    }
    
    #ifdef DEBUG;
      // Debugging.
      Serial.print(boxNum);
      Serial.print(" ");
      Serial.print(dir);
      Serial.print(" to ");
      Serial.println(state);
    #endif;
    
  } else if (command[0] == 'c') {
    
    // ---- Clear All ------------------------------------------------------------------------
    
    int time = DEFAULTCLEARTIME;
    
    // Check if a time value is given.
    if (command.length() > 1) {
      time = command.substring(1).toInt();
    }
    
    clear_all(time);
    
  } else if (command[0] == 't') {
    
    // ---- Pollution type ------------------------------------------------------------------------
    
    polType = (PollutionType)command.substring(1, 2).toInt();
    
  } else if (command[0] == 'b') {
    
    // ---- Target value --------------------------------------------------------------------------
    
    // Get the box number.
    byte boxNum = command.substring(1,2).toInt();
    
    long value = command.substring(2).toInt();
    
    #ifdef DEBUG;
      Serial.print("Setting box ");
      Serial.print(boxNum);
      Serial.print(" to ");
      Serial.println(value);
    #endif;
    
    if (boxNum >= 0 && boxNum < BOXAMOUNT) {
      if (value > 0) {
        // Set the value for this box.
        // Add the tube travel time for the relevant box.
        boxValues[boxNum] = (value * SMOKEMULTIPLIER) + BOXWAITINGTIMES[boxNum];
      }
    }
    
    #ifdef DEBUG;
      Serial.print("ms ");
      Serial.println(boxValues[boxNum]);
    #endif;
    
  } else if (command[0] == 'g') {
    
    // ---- Execute orders --------------------------------------------------------------------------

    execute_state();

  } else if (command[0] == 'm') {
    // Smoke machine.
    long value = command.substring(1).toInt();
    
    start_smoke_machine(value);
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
