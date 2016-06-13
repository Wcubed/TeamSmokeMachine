#include <Servo.h> //add the servo library
 
Servo myservo;  // create servo object to control a servo 

void set_valve(int cubeNum, int valveNum, boolean valveState;) {
  int valveOpen = 90;
  int valveClosed = 0;
  
  if(valveState) {
    valveServo[cubeNum][valveNum].write(valveOpen);
  } else {
    valveServo[cubeNum][valveNum].write(valveClosed);
  }
}
