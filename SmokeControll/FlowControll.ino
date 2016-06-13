// Controlls input / output flows.
// And the timing of them.


// Updates flow timers.
// Also closes a flow if a timer runs out.
void update_flow(long dt) {
  for (int i = 0; i < BOXAMOUNT; i++) {
    
    if (flowTimers[i][IN] > 0) {
      flowTimers[i][IN] -= dt; // Decrease the timer value;
      
      if (flowTimers[i][IN] <= 0) {
        // Timer has run out.
        stop_flow(i, IN);
      }
    }
    
    if (flowTimers[i][OUT] > 0) {
      flowTimers[i][OUT] -= dt; // Decrease the timer value;
      
      if (flowTimers[i][OUT] <= 0) {
        // Timer has run out.
        stop_flow(i, OUT);
      }
    }
  }
  
  // Smoke timer.
  
  if (smokeTimer > 0) {
    smokeTimer -= dt;
    
    if (smokeTimer <= 0) {
      // Turn smoke machine off.
      digitalWrite(smokePin, OFF);
    }
  }
}


// Stops a flow.
// Also resets the corresponding flow timer, if one was set.
void stop_flow(int boxNum, boolean dir) {
  set_fan(boxNum, dir, OFF);
  set_valve(boxNum, dir, OFF);
  
  flowTimers[boxNum][dir] = 0; // Reset the flow timer.
}


// Starts a flow with a certain time.
// Time is in milliseconds.
void start_flow(int boxNum, boolean dir, int time) {
  set_fan(boxNum, dir, ON);
  set_valve(boxNum, dir, ON);
  
  flowTimers[boxNum][dir] = time; // Start the flow timer.
}