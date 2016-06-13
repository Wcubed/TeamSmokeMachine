// All functions for controlling the fans.


// Configures the fan pins correctly.
void setup_fans() {
  
  for (int i = 0; i < BOXAMOUNT; i++) {
    // Set all pins to output
    pinMode(fanPins[i][IN], OUTPUT);
    pinMode(fanPins[i][OUT], OUTPUT);
  }
  
}


// Sets a fan to a certain speed.
//
// box: Box number => 0 - 4.
// dir: Direction of the smoke, either IN or OUT.
// state: Either ON or OFF.
void set_fan(int box, boolean dir, boolean state) {
  
  digitalWrite(fanPins[box][dir], state);
  
}


// Stops all fans.
void stop_all_fans() {
   for (int i = 0; i < BOXAMOUNT; i++) {
      set_fan(i, IN, OFF);
      set_fan(i, OUT, OFF);
   } 
}
