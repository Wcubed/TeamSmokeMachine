

// Opens or closes a valve.
//
// boxNum: Box number.
// dir: Direction, either IN or OUT.
// valveState: Either ON or OFF.
void set_valve(int boxNum, boolean dir, boolean valveState) {
  int valveOpen = 110;
  int valveClosed = 20;
  
  if(valveState == ON) {
    
    /*if (boxNum == 2 && dir == IN) { // Special case for the middle box, open the valve a little less.
      turn_servo(boxNum, dir, valveOpen - 40);
    } else {*/
      turn_servo(boxNum, dir, valveOpen);
    //}
  } else {
    turn_servo(boxNum, dir, valveClosed);
  }
}


// Closes all valves.
void close_all_valves() {
   for (int i = 0; i < BOXAMOUNT+1; i++) {
      set_valve(i, IN, OFF);
      set_valve(i, OUT, OFF);
   } 
}
