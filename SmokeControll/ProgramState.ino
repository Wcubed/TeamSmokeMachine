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
    
    // Make sure there is smoke in the buffer.
    start_smoke_machine(200);
    
    
    // Advance the program state.
    programState = CLEARING;
    
    clear_all(DEFAULTCLEARTIME);
    stateTimer = DEFAULTCLEARTIME + STATEWAITINGTIME;
  }
}


void update_state(long dt) {
  if (stateTimer > 0) {
    stateTimer -= dt;
  }
  
  if (stateTimer <= 0) {
    // Timer has run out, check what to do.
    
    if (programState == IDLE) { // -----------------------------------------------------
      return; // Nothing to do here.
      
    } else if (programState == CLEARING) { // ------------------------------------------
      Serial.println("Clearing is done, start filling");
      // Clearing is done, start filling.
      programState = FILLING;
      
      // Open the buffer valve.
      set_valve(5, OUT, ON);
      
      // Start with the first box.
      currentTargetBox = 0;
      
    } else if (programState == FILLING) { // -------------------------------------------
            
      if (currentTargetBox < BOXAMOUNT) {
        
        // Start the flow only if there needs to be smoke in the first place.
        if (targetBoxValues[currentTargetBox] > 0) {
          start_flow(currentTargetBox, IN, targetBoxValues[currentTargetBox]);
          
          stateTimer = targetBoxValues[currentTargetBox] + STATEWAITINGTIME;
        }
        
        // Next box.
        currentTargetBox++;
      
      } else {
        // Done filling, idle.
        programState = IDLE;
        
        // Close the buffer valve.
        set_valve(5, OUT, OFF);
      }
    } // -------------------------------------------------------------------------------
  }
}
