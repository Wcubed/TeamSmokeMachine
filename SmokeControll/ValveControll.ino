

// Opens or closes a valve.
//
// boxNum: Box number.
// dir: Direction, either IN or OUT.
// valveState: Either ON or OFF.
void set_valve(int boxNum, boolean dir, boolean valveState) {
  int valveOpen = 110;
  int valveClosed = 20;
  
  if(valveState == ON) {
    valveServos[boxNum][dir].write(valveOpen);
  } else {
    valveServos[boxNum][dir].write(valveClosed);
  }
}


// Closes all valves.
void close_all_valves() {
   for (int i = 0; i < BOXAMOUNT; i++) {
      set_valve(i, IN, OFF);
      set_valve(i, OUT, OFF);
   } 
}
