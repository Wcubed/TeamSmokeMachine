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

// Fan control pin numbers.
const int fanPins[BOXAMOUNT][2] = {
  {1, 2},
  {3, 4},
  {5, 6},
  {7, 8},
  {9, 10}
};

// Valve control pin numbers.
const int valvePins[BOXAMOUNT][2] = {
  {1, 2},
  {3, 4},
  {5, 6},
  {7, 8},
  {9, 10}
};


Servo valveServos[BOXAMOUNT][2];
