#include <Servo.h> //add the servo library

// Direction variables.
const bool IN = 0;
const bool OUT = 1;

// State variables.
const bool ON = true;
const bool OFF = false;


// Number of boxes.
const int BOXAMOUNT = 5;

// ---- Pin numbers -----------------------------------------------

const int smokePin = 32;

// Fan control pin numbers.
const int fanPins[BOXAMOUNT][2] = {
  {22, 23},
  {24, 25},
  {26, 27},
  {28, 29},
  {30, 31}
};

// Valve control pin numbers.
const int valvePins[BOXAMOUNT][2] = {
  {2, 3},
  {4, 5},
  {6, 7},
  {8, 9},
  {10, 11}
};

// ---- /Pin numbers -----------------------------------------------


// Holds the servo values.
Servo valveServos[BOXAMOUNT][2];


// Flow timers.
// Are set when input/output flow begins.
// Decrease over time (milliseconds).
// When one reaches 0 the corresponding valve/fan combination stops.
int flowTimers[BOXAMOUNT][2];
int smokeTimer; // Timer for the smoke machine.
