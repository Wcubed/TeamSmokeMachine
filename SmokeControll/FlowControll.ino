// Controlls input / output flows.
// And the timing of them.


void setup_state() {
  for (int i = 0; i < BOXAMOUNT; i++) {
    boxValues[i] = 0;
  }
  
  pinMode(smokePin, OUTPUT);
}


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
      digitalWrite(smokePin, LOW);
    }
  }
  
  // Smoke valve timer.
  if (smokeValveTimer > 0) {
    smokeValveTimer -= dt;
    
    if (smokeValveTimer <= 0) {
      set_valve(5, IN, OFF);
    }
  }
}


// Stops a flow.
// Also resets the corresponding flow timer, if one was set.
void stop_flow(int boxNum, boolean dir) {
  set_fan(boxNum, dir, OFF);
  set_valve(boxNum, dir, OFF);
  
  // If the flow is IN, the OUT valve will have been opened and will need to be closed as well.
  if (dir == IN) {
    set_valve(boxNum, OUT, OFF);
  }
  
  flowTimers[boxNum][dir] = 0; // Reset the flow timer.
}


// Starts a flow with a certain time.
// Time is in milliseconds.
void start_flow(int boxNum, boolean dir, int time) {
  set_fan(boxNum, dir, ON);
  set_valve(boxNum, dir, ON);
  
  // If the flow is IN, the OUT valve needs to be opened as well.
  if (dir == IN) {
    set_valve(boxNum, OUT, ON);
  }
  
  flowTimers[boxNum][dir] = time; // Start the flow timer.
}


// Clears all boxes.
void clear_all(int time) {
  for (int i = 0; i < BOXAMOUNT; i++) {
    start_flow(i, OUT, time);
  }
}

// Starts the smoke machine.
void start_smoke_machine(int time) {
  digitalWrite(smokePin, HIGH);
  smokeTimer = time;
  
  set_valve(5, IN, ON);
  smokeValveTimer = time + SMOKEGRACETIME;
}
