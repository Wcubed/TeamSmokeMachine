// High level smoke controll.


// Starts the clearing of the boxes.
// Sets the program for filling the boxes, after they have been cleared.
void execute_state() {
  
  // Only execute the command if currently idle.
  if (programState == IDLE) {
  
    // Transfer currently stored orders to the target variables.
    targetPolType = polType;
    
    for (int i = 0; i < BOXAMOUNT; i++) {
      targetBoxValues[i] = boxValues[i];
    }
    
    // Advance the program state.
    programState = CLEARING;
    
    clear_all(DEFAULTCLEARTIME);
    stateTimer = DEFAULTCLEARTIME + 100;
  }
}


void update_state(long dt) {
  if (stateTimer > 0) {
    stateTimer -= dt;
    
    if (stateTimer < 0) {
      // Timer has run out, check what to do.
      
      if (programState == IDLE) {
        return; // Nothing to do here.
        
      } else if (programState == CLEARING) {
        // Clearing is done, start filling.
        programState = FILLING;
        
        // Start with the first box.
        currentTargetBox = 0;
        
        // Start it's flow.
        start_flow(currentTargetBox, IN, targetBoxValues[currentTargetBox]);
        stateTimer = targetBoxValues[currentTargetBox];
        
      } else if (programState == FILLING) {
        
        // Next box.
        currentTargetBox++;
        
        if (currentTargetBox < BOXAMOUNT) {
          
          start_flow(currentTargetBox, IN, targetBoxValues[currentTargetBox]);
          stateTimer = targetBoxValues[currentTargetBox];
          
        } else {
          // Done filling, idle.
          programState = IDLE;
          stateTimer = 1; // So that the IDLE branch of this update function get's called on the next pass.
        }
      }
    }
  }
}
