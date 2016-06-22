#include <Servo.h> //add the servo library


// Turns the servo to the supplied angle.
void turn_servo(int boxNum, boolean dir, int angle) {
  // Attach the servo.
  valveServos[boxNum][dir].attach(valvePins[boxNum][dir]);
  
  // Start turning the servo to the new angle.
  valveServos[boxNum][dir].write(angle);
  
  // Set the timer for detaching this servo.
  servoTimers[boxNum][dir] = SERVOATTACHTIME;
}


// Decreases the servo timers.
// Detaches any servo who's time reaches 0.
void update_servos(long dt) {
  
  for (int i = 0; i < BOXAMOUNT+1; i++) {
    if (servoTimers[i][IN] > 0) {
      servoTimers[i][IN] -= dt;

      if (servoTimers[i][IN] <= 0) {
        // Detach the servo.
        valveServos[i][IN].detach();
      }
    }
    
    if (servoTimers[i][OUT] > 0) {
      servoTimers[i][OUT] -= dt;

      if (servoTimers[i][OUT] <= 0) {
        // Detach the servo.
        valveServos[i][OUT].detach();
      }
    }
  }
  
}

