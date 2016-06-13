#include <Servo.h> //add the servo library
 
Servo myservo;  // create servo object to control a servo 

// Opens or closes a valve.
//
// boxNum: Box number.
// valveNum: Either IN or OUT.
// valveState: Either ON or OFF.
void set_valve(int boxNum, int valveNum, boolean valveState;) {
  int valveOpen = 90;
  int valveClosed = 0;
  
  if(valveState) {
    valveServo[boxNum][valveNum].write(valveOpen);
  } else {
    valveServo[boxNum][valveNum].write(valveClosed);
  }
}
