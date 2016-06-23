#include <Servo.h> //add the servo library


void setup_servos() {
   for (int i = 0; i < BOXAMOUNT+1; i++) {
     servoTimers[i][IN] = 0;
     servoTimers[i][OUT] = 0;
   }
}


// Turns the servo to the supplied angle.
void turn_servo(int boxNum, boolean dir, int angle) {
  // Attach the servo.
  Serial.print("Boxnum in turnservo is: ");
  Serial.print(boxNum);
  Serial.print(" and dir is: ");
  Serial.print(dir);
  Serial.print(" And angle is: ");
  Serial.println(angle);
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
        Serial.print("Detaching ");
        Serial.print(i);
        Serial.print(" ");
        Serial.println(IN);
      }
    }
    
    if (servoTimers[i][OUT] > 0) {
      servoTimers[i][OUT] -= dt;

      if (servoTimers[i][OUT] <= 0) {
        // Detach the servo.
        valveServos[i][OUT].detach();
        Serial.print("Detaching ");
        Serial.print(i);
        Serial.print(" ");
        Serial.println(OUT);
      }
    }
  }
  
}

