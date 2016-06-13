#include <Servo.h> //add the servo library

// Configures all valves.
void setup_valves() {
  
  for (int i = 0; i < BOXAMOUNT; i++) {
    // Attach the servo's.
    valveServos[i][IN].attach(valvePins[i][IN]);
    valveServos[i][OUT].attach(valvePins[i][OUT]);
  }
  
}

// Opens or closes a valve.
//
// boxNum: Box number.
// dir: Direction, either IN or OUT.
// valveState: Either ON or OFF.
void set_valve(int boxNum, boolean dir, boolean valveState) {
  int valveOpen = 90;
  int valveClosed = 0;
  
  if(valveState) {
    valveServos[boxNum][dir].write(valveOpen);
  } else {
    valveServos[boxNum][dir].write(valveClosed);
  }
}
