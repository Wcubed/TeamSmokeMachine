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
    
      #ifdef DEBUG;
        Serial.println("Clearing is done, start filling");
      #endif;
      
      // Clearing is done, start filling.
      programState = FILLING;
      
      // Open the buffer valve.
      //set_valve(5, OUT, ON);
      
      // Start with the first box.
      currentTargetBox = 0;
      
    } else if (programState == FILLING) { // -------------------------------------------
            
      if (currentTargetBox < BOXAMOUNT) {
        
        // Start the flow only if there needs to be smoke in the first place.
        if (targetBoxValues[currentTargetBox] > 0) {
          start_flow(currentTargetBox, IN, targetBoxValues[currentTargetBox]);
          
          stateTimer = targetBoxValues[currentTargetBox] + STATEWAITINGTIME;
          
          // Make sure there is smoke in the buffer.
          if (currentTargetBox == 0) {
            start_smoke_machine(1000);
          } else {
            start_smoke_machine(500);
          }
        }
        
        // Next box.
        currentTargetBox++;
      
      } else {
        // Done filling, idle.
        programState = IDLE;
        
        close_all_valves();
        stop_all_fans();
        
        // Close the buffer valve.
        //set_valve(5, OUT, OFF);
      }
    } // -------------------------------------------------------------------------------
  }
}
