#include <Servo.h> //add the servo library

// Direction variables.
const bool IN = 0;
const bool OUT = 1;

// State variables.
const bool ON = true;
const bool OFF = false;


// Number of boxes.
const int BOXAMOUNT = 5;

// Time needed to clear a box (in milliseconds).
const int DEFAULTCLEARTIME = 1500;


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
const int valvePins[BOXAMOUNT+1][2] = {
  {11, 10},
  {9, 8},
  {7, 6},
  {5, 4},
  {3, 2},
  {12, 13} // These are for the buffer / smoke machine.
};

// ---- /Pin numbers -----------------------------------------------


// Holds the servo values.
Servo valveServos[BOXAMOUNT+1][2];


// Flow timers.
// Are set when input/output flow begins.
// Decrease over time (milliseconds).
// When one reaches 0 the corresponding valve/fan combination stops.
int flowTimers[BOXAMOUNT][2];
int smokeTimer; // Timer for the smoke machine.


// Servo timers.
// When one runs out, a servo is detached. (This prevents jitter when the servo is ).
int servoTimers[BOXAMOUNT+1][2];
const int SERVOATTACHTIME = 500; // Time (in ms) a servo will be "attached" to the Arduino.
// 500 ms should be enough for the servos to move to the new position.


// ---- Smoke target control --------------------------------------
// High level control.

// Program states.
typedef enum {IDLE, CLEARING, FILLING} ProgramState;

ProgramState programState;

// Current state timer.
int stateTimer;

// Waiting time between actions (in milliseconds).
const int STATEWAITINGTIME = 200;
// Multiply incoming smoke values with this scalar.
const int SMOKEMULTIPLIER = 5;

// Current box being filled.
int currentTargetBox;

// Pollution types.
typedef enum {PM10, PM25, N02, O3} PollutionType;

PollutionType polType; // Pollution type.

// Box pollution values.
int boxValues[BOXAMOUNT];

// ---- Target values of current command being executed ----

PollutionType targetPolType;
int targetBoxValues[BOXAMOUNT];
